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
struct uart_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; struct omap8250_priv* private_data; } ;
struct uart_8250_port {int lcr; scalar_t__ dma; scalar_t__ ier; } ;
struct omap8250_priv {int /*<<< orphan*/  qos_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_FCR ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_LCR ; 
 int UART_LCR_SBC ; 
 int /*<<< orphan*/  UART_OMAP_WER ; 
 int /*<<< orphan*/  dev_pm_clear_wake_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  omap_8250_rx_dma_flush (struct uart_8250_port*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial8250_release_dma (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static void omap_8250_shutdown(struct uart_port *port)
{
	struct uart_8250_port *up = up_to_u8250p(port);
	struct omap8250_priv *priv = port->private_data;

	flush_work(&priv->qos_work);
	if (up->dma)
		omap_8250_rx_dma_flush(up);

	pm_runtime_get_sync(port->dev);

	serial_out(up, UART_OMAP_WER, 0);

	up->ier = 0;
	serial_out(up, UART_IER, 0);

	if (up->dma)
		serial8250_release_dma(up);

	/*
	 * Disable break condition and FIFOs
	 */
	if (up->lcr & UART_LCR_SBC)
		serial_out(up, UART_LCR, up->lcr & ~UART_LCR_SBC);
	serial_out(up, UART_FCR, UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);

	pm_runtime_mark_last_busy(port->dev);
	pm_runtime_put_autosuspend(port->dev);
	free_irq(port->irq, port);
	dev_pm_clear_wake_irq(port->dev);
}