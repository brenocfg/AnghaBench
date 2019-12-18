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
struct uart_port {unsigned long uartclk; int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; scalar_t__ membase; TYPE_1__* dev; } ;
struct ktermios {int c_cflag; int c_iflag; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 unsigned long BIT (int) ; 
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
 unsigned int MLB_USIO_ESCR_FLWEN ; 
 unsigned int MLB_USIO_ESCR_L_5BIT ; 
 unsigned int MLB_USIO_ESCR_L_6BIT ; 
 unsigned int MLB_USIO_ESCR_L_7BIT ; 
 unsigned int MLB_USIO_ESCR_L_8BIT ; 
 unsigned int MLB_USIO_ESCR_P ; 
 unsigned int MLB_USIO_ESCR_PEN ; 
 unsigned long MLB_USIO_FCR_FCL1 ; 
 unsigned long MLB_USIO_FCR_FCL2 ; 
 unsigned long MLB_USIO_FCR_FE1 ; 
 unsigned long MLB_USIO_FCR_FE2 ; 
 unsigned long MLB_USIO_FCR_FRIIE ; 
 scalar_t__ MLB_USIO_REG_BGR ; 
 scalar_t__ MLB_USIO_REG_ESCR ; 
 scalar_t__ MLB_USIO_REG_FBYTE ; 
 scalar_t__ MLB_USIO_REG_FCR ; 
 scalar_t__ MLB_USIO_REG_SCR ; 
 scalar_t__ MLB_USIO_REG_SMR ; 
 scalar_t__ MLB_USIO_REG_SSR ; 
 unsigned int MLB_USIO_SCR_RIE ; 
 unsigned int MLB_USIO_SCR_RXE ; 
 unsigned int MLB_USIO_SCR_TBIE ; 
 unsigned int MLB_USIO_SCR_TXE ; 
 unsigned int MLB_USIO_SCR_UPCL ; 
 unsigned int MLB_USIO_SMR_SBL ; 
 unsigned int MLB_USIO_SMR_SOE ; 
 int MLB_USIO_SSR_FRE ; 
 int MLB_USIO_SSR_ORE ; 
 int MLB_USIO_SSR_PE ; 
 int MLB_USIO_SSR_RDRF ; 
 unsigned int MLB_USIO_SSR_REC ; 
 int MLB_USIO_SSR_TDRE ; 
 int PARENB ; 
 int PARODD ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned long) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  writew (unsigned long,scalar_t__) ; 

__attribute__((used)) static void mlb_usio_set_termios(struct uart_port *port,
			struct ktermios *termios, struct ktermios *old)
{
	unsigned int escr, smr = MLB_USIO_SMR_SOE;
	unsigned long flags, baud, quot;

	switch (termios->c_cflag & CSIZE) {
	case CS5:
		escr = MLB_USIO_ESCR_L_5BIT;
		break;
	case CS6:
		escr = MLB_USIO_ESCR_L_6BIT;
		break;
	case CS7:
		escr = MLB_USIO_ESCR_L_7BIT;
		break;
	case CS8:
	default:
		escr = MLB_USIO_ESCR_L_8BIT;
		break;
	}

	if (termios->c_cflag & CSTOPB)
		smr |= MLB_USIO_SMR_SBL;

	if (termios->c_cflag & PARENB) {
		escr |= MLB_USIO_ESCR_PEN;
		if (termios->c_cflag & PARODD)
			escr |= MLB_USIO_ESCR_P;
	}
	/* Set hard flow control */
	if (of_property_read_bool(port->dev->of_node, "auto-flow-control") ||
			(termios->c_cflag & CRTSCTS))
		escr |= MLB_USIO_ESCR_FLWEN;

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk);
	if (baud > 1)
		quot = port->uartclk / baud - 1;
	else
		quot = 0;

	spin_lock_irqsave(&port->lock, flags);
	uart_update_timeout(port, termios->c_cflag, baud);
	port->read_status_mask = MLB_USIO_SSR_ORE | MLB_USIO_SSR_RDRF |
				 MLB_USIO_SSR_TDRE;
	if (termios->c_iflag & INPCK)
		port->read_status_mask |= MLB_USIO_SSR_FRE | MLB_USIO_SSR_PE;

	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask |= MLB_USIO_SSR_FRE | MLB_USIO_SSR_PE;
	if ((termios->c_iflag & IGNBRK) && (termios->c_iflag & IGNPAR))
		port->ignore_status_mask |= MLB_USIO_SSR_ORE;
	if ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= MLB_USIO_SSR_RDRF;

	writeb(0, port->membase + MLB_USIO_REG_SCR);
	writeb(MLB_USIO_SCR_UPCL, port->membase + MLB_USIO_REG_SCR);
	writeb(MLB_USIO_SSR_REC, port->membase + MLB_USIO_REG_SSR);
	writew(0, port->membase + MLB_USIO_REG_FCR);
	writeb(smr, port->membase + MLB_USIO_REG_SMR);
	writeb(escr, port->membase + MLB_USIO_REG_ESCR);
	writew(quot, port->membase + MLB_USIO_REG_BGR);
	writew(0, port->membase + MLB_USIO_REG_FCR);
	writew(MLB_USIO_FCR_FCL1 | MLB_USIO_FCR_FCL2 | MLB_USIO_FCR_FE1 |
	       MLB_USIO_FCR_FE2 | MLB_USIO_FCR_FRIIE,
	       port->membase + MLB_USIO_REG_FCR);
	writew(0, port->membase + MLB_USIO_REG_FBYTE);
	writew(BIT(12), port->membase + MLB_USIO_REG_FBYTE);
	writeb(MLB_USIO_SCR_RIE | MLB_USIO_SCR_RXE | MLB_USIO_SCR_TBIE |
	       MLB_USIO_SCR_TXE, port->membase + MLB_USIO_REG_SCR);
	spin_unlock_irqrestore(&port->lock, flags);
}