#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uart_port {scalar_t__ mapbase; struct cdns_uart* private_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cdns_uart {scalar_t__ id; int /*<<< orphan*/  cdns_uart_driver; int /*<<< orphan*/  pclk; int /*<<< orphan*/  uartclk; int /*<<< orphan*/  clk_rate_change_nb; } ;

/* Variables and functions */
 scalar_t__ MAX_UART_INSTANCES ; 
 int /*<<< orphan*/  bitmap ; 
 scalar_t__ bitmap_empty (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_lock ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct uart_port* console_port ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct uart_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 int uart_remove_one_port (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  uart_unregister_driver (int /*<<< orphan*/ ) ; 
 scalar_t__ uartps_major ; 

__attribute__((used)) static int cdns_uart_remove(struct platform_device *pdev)
{
	struct uart_port *port = platform_get_drvdata(pdev);
	struct cdns_uart *cdns_uart_data = port->private_data;
	int rc;

	/* Remove the cdns_uart port from the serial core */
#ifdef CONFIG_COMMON_CLK
	clk_notifier_unregister(cdns_uart_data->uartclk,
			&cdns_uart_data->clk_rate_change_nb);
#endif
	rc = uart_remove_one_port(cdns_uart_data->cdns_uart_driver, port);
	port->mapbase = 0;
	mutex_lock(&bitmap_lock);
	if (cdns_uart_data->id < MAX_UART_INSTANCES)
		clear_bit(cdns_uart_data->id, bitmap);
	mutex_unlock(&bitmap_lock);
	clk_disable_unprepare(cdns_uart_data->uartclk);
	clk_disable_unprepare(cdns_uart_data->pclk);
	pm_runtime_disable(&pdev->dev);
	pm_runtime_set_suspended(&pdev->dev);
	pm_runtime_dont_use_autosuspend(&pdev->dev);
	device_init_wakeup(&pdev->dev, false);

#ifdef CONFIG_SERIAL_XILINX_PS_UART_CONSOLE
	if (console_port == port)
		console_port = NULL;
#endif

	/* If this is last instance major number should be initialized */
	mutex_lock(&bitmap_lock);
	if (bitmap_empty(bitmap, MAX_UART_INSTANCES))
		uartps_major = 0;
	mutex_unlock(&bitmap_lock);

	uart_unregister_driver(cdns_uart_data->cdns_uart_driver);
	return rc;
}