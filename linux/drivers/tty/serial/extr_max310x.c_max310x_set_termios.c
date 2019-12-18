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
struct uart_port {int read_status_mask; int ignore_status_mask; int status; int uartclk; } ;
struct ktermios {int c_cflag; int c_iflag; unsigned int* c_cc; } ;

/* Variables and functions */
 int BRKINT ; 
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
 int INPCK ; 
 int IXOFF ; 
 int IXON ; 
 unsigned int MAX310X_FLOWCTRL_AUTOCTS_BIT ; 
 unsigned int MAX310X_FLOWCTRL_AUTORTS_BIT ; 
 int /*<<< orphan*/  MAX310X_FLOWCTRL_REG ; 
 unsigned int MAX310X_FLOWCTRL_SWFLOW1_BIT ; 
 unsigned int MAX310X_FLOWCTRL_SWFLOW3_BIT ; 
 unsigned int MAX310X_FLOWCTRL_SWFLOWEN_BIT ; 
 unsigned int MAX310X_LCR_EVENPARITY_BIT ; 
 unsigned int MAX310X_LCR_LENGTH0_BIT ; 
 unsigned int MAX310X_LCR_LENGTH1_BIT ; 
 unsigned int MAX310X_LCR_PARITY_BIT ; 
 int /*<<< orphan*/  MAX310X_LCR_REG ; 
 unsigned int MAX310X_LCR_STOPLEN_BIT ; 
 int MAX310X_LSR_FRERR_BIT ; 
 int MAX310X_LSR_RXBRK_BIT ; 
 int MAX310X_LSR_RXOVR_BIT ; 
 int MAX310X_LSR_RXPAR_BIT ; 
 int /*<<< orphan*/  MAX310X_MODE1_REG ; 
 int /*<<< orphan*/  MAX310X_MODE1_TXDIS_BIT ; 
 int /*<<< orphan*/  MAX310X_XOFF1_REG ; 
 int /*<<< orphan*/  MAX310X_XON1_REG ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int UPSTAT_AUTOCTS ; 
 int UPSTAT_AUTORTS ; 
 int UPSTAT_AUTOXOFF ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  max310x_port_update (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max310x_port_write (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int max310x_set_baud (struct uart_port*,int) ; 
 int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,int) ; 

__attribute__((used)) static void max310x_set_termios(struct uart_port *port,
				struct ktermios *termios,
				struct ktermios *old)
{
	unsigned int lcr = 0, flow = 0;
	int baud;

	/* Mask termios capabilities we don't support */
	termios->c_cflag &= ~CMSPAR;

	/* Word size */
	switch (termios->c_cflag & CSIZE) {
	case CS5:
		break;
	case CS6:
		lcr = MAX310X_LCR_LENGTH0_BIT;
		break;
	case CS7:
		lcr = MAX310X_LCR_LENGTH1_BIT;
		break;
	case CS8:
	default:
		lcr = MAX310X_LCR_LENGTH1_BIT | MAX310X_LCR_LENGTH0_BIT;
		break;
	}

	/* Parity */
	if (termios->c_cflag & PARENB) {
		lcr |= MAX310X_LCR_PARITY_BIT;
		if (!(termios->c_cflag & PARODD))
			lcr |= MAX310X_LCR_EVENPARITY_BIT;
	}

	/* Stop bits */
	if (termios->c_cflag & CSTOPB)
		lcr |= MAX310X_LCR_STOPLEN_BIT; /* 2 stops */

	/* Update LCR register */
	max310x_port_write(port, MAX310X_LCR_REG, lcr);

	/* Set read status mask */
	port->read_status_mask = MAX310X_LSR_RXOVR_BIT;
	if (termios->c_iflag & INPCK)
		port->read_status_mask |= MAX310X_LSR_RXPAR_BIT |
					  MAX310X_LSR_FRERR_BIT;
	if (termios->c_iflag & (IGNBRK | BRKINT | PARMRK))
		port->read_status_mask |= MAX310X_LSR_RXBRK_BIT;

	/* Set status ignore mask */
	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNBRK)
		port->ignore_status_mask |= MAX310X_LSR_RXBRK_BIT;
	if (!(termios->c_cflag & CREAD))
		port->ignore_status_mask |= MAX310X_LSR_RXPAR_BIT |
					    MAX310X_LSR_RXOVR_BIT |
					    MAX310X_LSR_FRERR_BIT |
					    MAX310X_LSR_RXBRK_BIT;

	/* Configure flow control */
	max310x_port_write(port, MAX310X_XON1_REG, termios->c_cc[VSTART]);
	max310x_port_write(port, MAX310X_XOFF1_REG, termios->c_cc[VSTOP]);

	/* Disable transmitter before enabling AutoCTS or auto transmitter
	 * flow control
	 */
	if (termios->c_cflag & CRTSCTS || termios->c_iflag & IXOFF) {
		max310x_port_update(port, MAX310X_MODE1_REG,
				    MAX310X_MODE1_TXDIS_BIT,
				    MAX310X_MODE1_TXDIS_BIT);
	}

	port->status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTORTS | UPSTAT_AUTOXOFF);

	if (termios->c_cflag & CRTSCTS) {
		/* Enable AUTORTS and AUTOCTS */
		port->status |= UPSTAT_AUTOCTS | UPSTAT_AUTORTS;
		flow |= MAX310X_FLOWCTRL_AUTOCTS_BIT |
			MAX310X_FLOWCTRL_AUTORTS_BIT;
	}
	if (termios->c_iflag & IXON)
		flow |= MAX310X_FLOWCTRL_SWFLOW3_BIT |
			MAX310X_FLOWCTRL_SWFLOWEN_BIT;
	if (termios->c_iflag & IXOFF) {
		port->status |= UPSTAT_AUTOXOFF;
		flow |= MAX310X_FLOWCTRL_SWFLOW1_BIT |
			MAX310X_FLOWCTRL_SWFLOWEN_BIT;
	}
	max310x_port_write(port, MAX310X_FLOWCTRL_REG, flow);

	/* Enable transmitter after disabling AutoCTS and auto transmitter
	 * flow control
	 */
	if (!(termios->c_cflag & CRTSCTS) && !(termios->c_iflag & IXOFF)) {
		max310x_port_update(port, MAX310X_MODE1_REG,
				    MAX310X_MODE1_TXDIS_BIT,
				    0);
	}

	/* Get baud rate generator configuration */
	baud = uart_get_baud_rate(port, termios, old,
				  port->uartclk / 16 / 0xffff,
				  port->uartclk / 4);

	/* Setup baudrate generator */
	baud = max310x_set_baud(port, baud);

	/* Update timeout according to new baud rate */
	uart_update_timeout(port, termios->c_cflag, baud);
}