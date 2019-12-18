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
struct uart_port {int uartclk; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int read_status_mask; int ignore_status_mask; int status; int flags; int /*<<< orphan*/  lock; struct omap8250_priv* private_data; } ;
struct uart_8250_port {unsigned char lcr; int fcr; TYPE_1__ port; int /*<<< orphan*/  gpios; scalar_t__ dma; int /*<<< orphan*/  ier; } ;
struct omap8250_priv {int scr; int calc_latency; int latency; int /*<<< orphan*/  qos_work; int /*<<< orphan*/  efr; int /*<<< orphan*/  xoff; int /*<<< orphan*/  xon; } ;
struct ktermios {int c_cflag; int c_iflag; int /*<<< orphan*/ * c_cc; } ;

/* Variables and functions */
 int CMSPAR ; 
 int CREAD ; 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int IXOFF ; 
 int OMAP_UART_FCR_RX_TRIG ; 
 int OMAP_UART_FCR_TX_TRIG ; 
 int OMAP_UART_SCR_DMAMODE_1 ; 
 int OMAP_UART_SCR_DMAMODE_CTL ; 
 int OMAP_UART_SCR_RX_TRIG_GRANU1_MASK ; 
 int OMAP_UART_SCR_TX_EMPTY ; 
 int OMAP_UART_SCR_TX_TRIG_GRANU1_MASK ; 
 int /*<<< orphan*/  OMAP_UART_SW_TX ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int /*<<< orphan*/  RX_TRIGGER ; 
 int TRIGGER_FCR_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_TRIGGER ; 
 int UART_DIV_MAX ; 
 int /*<<< orphan*/  UART_EFR_CTS ; 
 scalar_t__ UART_ENABLE_MS (TYPE_1__*,int) ; 
 int UART_FCR_ENABLE_FIFO ; 
 int /*<<< orphan*/  UART_GPIO_CTS ; 
 int /*<<< orphan*/  UART_GPIO_RTS ; 
 int /*<<< orphan*/  UART_IER_MSI ; 
 unsigned char UART_LCR_EPAR ; 
 unsigned char UART_LCR_PARITY ; 
 unsigned char UART_LCR_SPAR ; 
 unsigned char UART_LCR_STOP ; 
 unsigned char UART_LCR_WLEN5 ; 
 unsigned char UART_LCR_WLEN6 ; 
 unsigned char UART_LCR_WLEN7 ; 
 unsigned char UART_LCR_WLEN8 ; 
 int UART_LSR_BI ; 
 int UART_LSR_DR ; 
 int UART_LSR_FE ; 
 int UART_LSR_OE ; 
 int UART_LSR_PE ; 
 int UART_LSR_THRE ; 
 int UPF_HARD_FLOW ; 
 int UPF_SOFT_FLOW ; 
 int UPSTAT_AUTOCTS ; 
 int UPSTAT_AUTORTS ; 
 int UPSTAT_AUTOXOFF ; 
 int USEC_PER_SEC ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  mctrl_gpio_to_gpiod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap8250_restore_regs (struct uart_8250_port*) ; 
 int /*<<< orphan*/  omap_8250_get_divisor (struct uart_port*,unsigned int,struct omap8250_priv*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,unsigned int,unsigned int) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static void omap_8250_set_termios(struct uart_port *port,
				  struct ktermios *termios,
				  struct ktermios *old)
{
	struct uart_8250_port *up = up_to_u8250p(port);
	struct omap8250_priv *priv = up->port.private_data;
	unsigned char cval = 0;
	unsigned int baud;

	switch (termios->c_cflag & CSIZE) {
	case CS5:
		cval = UART_LCR_WLEN5;
		break;
	case CS6:
		cval = UART_LCR_WLEN6;
		break;
	case CS7:
		cval = UART_LCR_WLEN7;
		break;
	default:
	case CS8:
		cval = UART_LCR_WLEN8;
		break;
	}

	if (termios->c_cflag & CSTOPB)
		cval |= UART_LCR_STOP;
	if (termios->c_cflag & PARENB)
		cval |= UART_LCR_PARITY;
	if (!(termios->c_cflag & PARODD))
		cval |= UART_LCR_EPAR;
	if (termios->c_cflag & CMSPAR)
		cval |= UART_LCR_SPAR;

	/*
	 * Ask the core to calculate the divisor for us.
	 */
	baud = uart_get_baud_rate(port, termios, old,
				  port->uartclk / 16 / UART_DIV_MAX,
				  port->uartclk / 13);
	omap_8250_get_divisor(port, baud, priv);

	/*
	 * Ok, we're now changing the port state. Do it with
	 * interrupts disabled.
	 */
	pm_runtime_get_sync(port->dev);
	spin_lock_irq(&port->lock);

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	up->port.read_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	if (termios->c_iflag & INPCK)
		up->port.read_status_mask |= UART_LSR_FE | UART_LSR_PE;
	if (termios->c_iflag & (IGNBRK | PARMRK))
		up->port.read_status_mask |= UART_LSR_BI;

	/*
	 * Characters to ignore
	 */
	up->port.ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		up->port.ignore_status_mask |= UART_LSR_PE | UART_LSR_FE;
	if (termios->c_iflag & IGNBRK) {
		up->port.ignore_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			up->port.ignore_status_mask |= UART_LSR_OE;
	}

	/*
	 * ignore all characters if CREAD is not set
	 */
	if ((termios->c_cflag & CREAD) == 0)
		up->port.ignore_status_mask |= UART_LSR_DR;

	/*
	 * Modem status interrupts
	 */
	up->ier &= ~UART_IER_MSI;
	if (UART_ENABLE_MS(&up->port, termios->c_cflag))
		up->ier |= UART_IER_MSI;

	up->lcr = cval;
	/* Up to here it was mostly serial8250_do_set_termios() */

	/*
	 * We enable TRIG_GRANU for RX and TX and additionally we set
	 * SCR_TX_EMPTY bit. The result is the following:
	 * - RX_TRIGGER amount of bytes in the FIFO will cause an interrupt.
	 * - less than RX_TRIGGER number of bytes will also cause an interrupt
	 *   once the UART decides that there no new bytes arriving.
	 * - Once THRE is enabled, the interrupt will be fired once the FIFO is
	 *   empty - the trigger level is ignored here.
	 *
	 * Once DMA is enabled:
	 * - UART will assert the TX DMA line once there is room for TX_TRIGGER
	 *   bytes in the TX FIFO. On each assert the DMA engine will move
	 *   TX_TRIGGER bytes into the FIFO.
	 * - UART will assert the RX DMA line once there are RX_TRIGGER bytes in
	 *   the FIFO and move RX_TRIGGER bytes.
	 * This is because threshold and trigger values are the same.
	 */
	up->fcr = UART_FCR_ENABLE_FIFO;
	up->fcr |= TRIGGER_FCR_MASK(TX_TRIGGER) << OMAP_UART_FCR_TX_TRIG;
	up->fcr |= TRIGGER_FCR_MASK(RX_TRIGGER) << OMAP_UART_FCR_RX_TRIG;

	priv->scr = OMAP_UART_SCR_RX_TRIG_GRANU1_MASK | OMAP_UART_SCR_TX_EMPTY |
		OMAP_UART_SCR_TX_TRIG_GRANU1_MASK;

	if (up->dma)
		priv->scr |= OMAP_UART_SCR_DMAMODE_1 |
			OMAP_UART_SCR_DMAMODE_CTL;

	priv->xon = termios->c_cc[VSTART];
	priv->xoff = termios->c_cc[VSTOP];

	priv->efr = 0;
	up->port.status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTORTS | UPSTAT_AUTOXOFF);

	if (termios->c_cflag & CRTSCTS && up->port.flags & UPF_HARD_FLOW &&
	    !mctrl_gpio_to_gpiod(up->gpios, UART_GPIO_RTS) &&
	    !mctrl_gpio_to_gpiod(up->gpios, UART_GPIO_CTS)) {
		/* Enable AUTOCTS (autoRTS is enabled when RTS is raised) */
		up->port.status |= UPSTAT_AUTOCTS | UPSTAT_AUTORTS;
		priv->efr |= UART_EFR_CTS;
	} else	if (up->port.flags & UPF_SOFT_FLOW) {
		/*
		 * OMAP rx s/w flow control is borked; the transmitter remains
		 * stuck off even if rx flow control is subsequently disabled
		 */

		/*
		 * IXOFF Flag:
		 * Enable XON/XOFF flow control on output.
		 * Transmit XON1, XOFF1
		 */
		if (termios->c_iflag & IXOFF) {
			up->port.status |= UPSTAT_AUTOXOFF;
			priv->efr |= OMAP_UART_SW_TX;
		}
	}
	omap8250_restore_regs(up);

	spin_unlock_irq(&up->port.lock);
	pm_runtime_mark_last_busy(port->dev);
	pm_runtime_put_autosuspend(port->dev);

	/* calculate wakeup latency constraint */
	priv->calc_latency = USEC_PER_SEC * 64 * 8 / baud;
	priv->latency = priv->calc_latency;

	schedule_work(&priv->qos_work);

	/* Don't rewrite B0 */
	if (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);
}