#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct sifive_serial_port {int /*<<< orphan*/  clk_notifier; int /*<<< orphan*/  clk; TYPE_1__ port; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ssp_remove_console_port (struct sifive_serial_port*) ; 
 int /*<<< orphan*/  clk_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sifive_serial_port*) ; 
 struct sifive_serial_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sifive_serial_uart_driver ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int sifive_serial_remove(struct platform_device *dev)
{
	struct sifive_serial_port *ssp = platform_get_drvdata(dev);

	__ssp_remove_console_port(ssp);
	uart_remove_one_port(&sifive_serial_uart_driver, &ssp->port);
	free_irq(ssp->port.irq, ssp);
	clk_notifier_unregister(ssp->clk, &ssp->clk_notifier);

	return 0;
}