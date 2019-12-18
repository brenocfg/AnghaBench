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
struct uart_port {int dummy; } ;
struct stm32_usart_offsets {int /*<<< orphan*/  cr3; } ;
struct stm32_port {scalar_t__ wakeirq; int /*<<< orphan*/  clk; scalar_t__ tx_dma_buf; int /*<<< orphan*/  tx_buf; scalar_t__ tx_ch; scalar_t__ rx_dma_buf; int /*<<< orphan*/  rx_buf; scalar_t__ rx_ch; TYPE_1__* info; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_BUF_L ; 
 int /*<<< orphan*/  TX_BUF_L ; 
 int /*<<< orphan*/  USART_CR3_DMAR ; 
 int /*<<< orphan*/  USART_CR3_DMAT ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_clear_wake_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 struct uart_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_clr_bits (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_usart_driver ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 
 int uart_remove_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int stm32_serial_remove(struct platform_device *pdev)
{
	struct uart_port *port = platform_get_drvdata(pdev);
	struct stm32_port *stm32_port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32_port->info->ofs;
	int err;

	pm_runtime_get_sync(&pdev->dev);

	stm32_clr_bits(port, ofs->cr3, USART_CR3_DMAR);

	if (stm32_port->rx_ch)
		dma_release_channel(stm32_port->rx_ch);

	if (stm32_port->rx_dma_buf)
		dma_free_coherent(&pdev->dev,
				  RX_BUF_L, stm32_port->rx_buf,
				  stm32_port->rx_dma_buf);

	stm32_clr_bits(port, ofs->cr3, USART_CR3_DMAT);

	if (stm32_port->tx_ch)
		dma_release_channel(stm32_port->tx_ch);

	if (stm32_port->tx_dma_buf)
		dma_free_coherent(&pdev->dev,
				  TX_BUF_L, stm32_port->tx_buf,
				  stm32_port->tx_dma_buf);

	if (stm32_port->wakeirq > 0) {
		dev_pm_clear_wake_irq(&pdev->dev);
		device_init_wakeup(&pdev->dev, false);
	}

	clk_disable_unprepare(stm32_port->clk);

	err = uart_remove_one_port(&stm32_usart_driver, port);

	pm_runtime_disable(&pdev->dev);
	pm_runtime_put_noidle(&pdev->dev);

	return err;
}