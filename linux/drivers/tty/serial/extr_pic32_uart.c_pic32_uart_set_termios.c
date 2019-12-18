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
struct uart_port {int uartclk; int /*<<< orphan*/  lock; } ;
struct pic32_sport {scalar_t__ hw_flow_ctrl; } ;
struct ktermios {int c_cflag; } ;

/* Variables and functions */
 int CMSPAR ; 
 int CRTSCTS ; 
 int CS8 ; 
 int CSTOPB ; 
 int PARENB ; 
 int PARODD ; 
 int /*<<< orphan*/  PIC32_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIC32_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIC32_UART_BRG ; 
 int /*<<< orphan*/  PIC32_UART_MODE ; 
 unsigned int PIC32_UART_MODE_PDSEL0 ; 
 unsigned int PIC32_UART_MODE_PDSEL1 ; 
 unsigned int PIC32_UART_MODE_RTSMD ; 
 unsigned int PIC32_UART_MODE_STSEL ; 
 unsigned int PIC32_UART_MODE_UEN0 ; 
 unsigned int PIC32_UART_MODE_UEN1 ; 
 int /*<<< orphan*/  pic32_uart_dsbl_and_mask (struct uart_port*) ; 
 int /*<<< orphan*/  pic32_uart_en_and_unmask (struct uart_port*) ; 
 int /*<<< orphan*/  pic32_uart_writel (struct pic32_sport*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pic32_sport* to_pic32_sport (struct uart_port*) ; 
 scalar_t__ tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,unsigned int,unsigned int) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int uart_get_divisor (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void pic32_uart_set_termios(struct uart_port *port,
				   struct ktermios *new,
				   struct ktermios *old)
{
	struct pic32_sport *sport = to_pic32_sport(port);
	unsigned int baud;
	unsigned int quot;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);

	/* disable uart and mask all interrupts while changing speed */
	pic32_uart_dsbl_and_mask(port);

	/* stop bit options */
	if (new->c_cflag & CSTOPB)
		pic32_uart_writel(sport, PIC32_SET(PIC32_UART_MODE),
					PIC32_UART_MODE_STSEL);
	else
		pic32_uart_writel(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_STSEL);

	/* parity options */
	if (new->c_cflag & PARENB) {
		if (new->c_cflag & PARODD) {
			pic32_uart_writel(sport, PIC32_SET(PIC32_UART_MODE),
					PIC32_UART_MODE_PDSEL1);
			pic32_uart_writel(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_PDSEL0);
		} else {
			pic32_uart_writel(sport, PIC32_SET(PIC32_UART_MODE),
					PIC32_UART_MODE_PDSEL0);
			pic32_uart_writel(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_PDSEL1);
		}
	} else {
		pic32_uart_writel(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_PDSEL1 |
					PIC32_UART_MODE_PDSEL0);
	}
	/* if hw flow ctrl, then the pins must be specified in device tree */
	if ((new->c_cflag & CRTSCTS) && sport->hw_flow_ctrl) {
		/* enable hardware flow control */
		pic32_uart_writel(sport, PIC32_SET(PIC32_UART_MODE),
					PIC32_UART_MODE_UEN1);
		pic32_uart_writel(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_UEN0);
		pic32_uart_writel(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_RTSMD);
	} else {
		/* disable hardware flow control */
		pic32_uart_writel(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_UEN1);
		pic32_uart_writel(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_UEN0);
		pic32_uart_writel(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_RTSMD);
	}

	/* Always 8-bit */
	new->c_cflag |= CS8;

	/* Mark/Space parity is not supported */
	new->c_cflag &= ~CMSPAR;

	/* update baud */
	baud = uart_get_baud_rate(port, new, old, 0, port->uartclk / 16);
	quot = uart_get_divisor(port, baud) - 1;
	pic32_uart_writel(sport, PIC32_UART_BRG, quot);
	uart_update_timeout(port, new->c_cflag, baud);

	if (tty_termios_baud_rate(new))
		tty_termios_encode_baud_rate(new, baud, baud);

	/* enable uart */
	pic32_uart_en_and_unmask(port);

	spin_unlock_irqrestore(&port->lock, flags);
}