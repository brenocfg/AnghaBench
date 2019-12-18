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
struct uart_port {unsigned long uartclk; int fifosize; int /*<<< orphan*/  lock; } ;
struct msm_port {int imr; scalar_t__ is_uartdm; int /*<<< orphan*/  clk; } ;
struct msm_baud_map {unsigned long divisor; int code; unsigned int rxstale; } ;

/* Variables and functions */
 int /*<<< orphan*/  UARTDM_DMRX ; 
 int /*<<< orphan*/  UART_CR ; 
 int UART_CR_CMD_PROTECTION_EN ; 
 int UART_CR_CMD_RESET_STALE_INT ; 
 int UART_CR_CMD_STALE_EVENT_ENABLE ; 
 int UART_CR_RX_ENABLE ; 
 int UART_CR_TX_ENABLE ; 
 int /*<<< orphan*/  UART_CSR ; 
 unsigned int UART_DM_IPR_STALE_TIMEOUT_MSB ; 
 int /*<<< orphan*/  UART_IMR ; 
 int UART_IMR_CURRENT_CTS ; 
 int UART_IMR_RXBREAK_START ; 
 int UART_IMR_RXLEV ; 
 int UART_IMR_RXSTALE ; 
 int /*<<< orphan*/  UART_IPR ; 
 unsigned int UART_IPR_RXSTALE_LAST ; 
 unsigned int UART_IPR_STALE_LSB ; 
 unsigned int UART_IPR_STALE_TIMEOUT_MSB ; 
 int /*<<< orphan*/  UART_RFWR ; 
 int /*<<< orphan*/  UART_TFWR ; 
 struct msm_port* UART_TO_MSM (struct uart_port*) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 struct msm_baud_map* msm_find_best_baud (struct uart_port*,unsigned int,unsigned long*) ; 
 int /*<<< orphan*/  msm_reset (struct uart_port*) ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int msm_set_baud_rate(struct uart_port *port, unsigned int baud,
			     unsigned long *saved_flags)
{
	unsigned int rxstale, watermark, mask;
	struct msm_port *msm_port = UART_TO_MSM(port);
	const struct msm_baud_map *entry;
	unsigned long flags, rate;

	flags = *saved_flags;
	spin_unlock_irqrestore(&port->lock, flags);

	entry = msm_find_best_baud(port, baud, &rate);
	clk_set_rate(msm_port->clk, rate);
	baud = rate / 16 / entry->divisor;

	spin_lock_irqsave(&port->lock, flags);
	*saved_flags = flags;
	port->uartclk = rate;

	msm_write(port, entry->code, UART_CSR);

	/* RX stale watermark */
	rxstale = entry->rxstale;
	watermark = UART_IPR_STALE_LSB & rxstale;
	if (msm_port->is_uartdm) {
		mask = UART_DM_IPR_STALE_TIMEOUT_MSB;
	} else {
		watermark |= UART_IPR_RXSTALE_LAST;
		mask = UART_IPR_STALE_TIMEOUT_MSB;
	}

	watermark |= mask & (rxstale << 2);

	msm_write(port, watermark, UART_IPR);

	/* set RX watermark */
	watermark = (port->fifosize * 3) / 4;
	msm_write(port, watermark, UART_RFWR);

	/* set TX watermark */
	msm_write(port, 10, UART_TFWR);

	msm_write(port, UART_CR_CMD_PROTECTION_EN, UART_CR);
	msm_reset(port);

	/* Enable RX and TX */
	msm_write(port, UART_CR_TX_ENABLE | UART_CR_RX_ENABLE, UART_CR);

	/* turn on RX and CTS interrupts */
	msm_port->imr = UART_IMR_RXLEV | UART_IMR_RXSTALE |
			UART_IMR_CURRENT_CTS | UART_IMR_RXBREAK_START;

	msm_write(port, msm_port->imr, UART_IMR);

	if (msm_port->is_uartdm) {
		msm_write(port, UART_CR_CMD_RESET_STALE_INT, UART_CR);
		msm_write(port, 0xFFFFFF, UARTDM_DMRX);
		msm_write(port, UART_CR_CMD_STALE_EVENT_ENABLE, UART_CR);
	}

	return baud;
}