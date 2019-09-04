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
struct sdio_uart_port {unsigned int uartclk; int read_status_mask; int ignore_status_mask; unsigned char ier; unsigned char lcr; int /*<<< orphan*/  mctrl; } ;
struct ktermios {int c_cflag; int c_iflag; } ;

/* Variables and functions */
 int B9600 ; 
 int BRKINT ; 
 int CBAUD ; 
 int CLOCAL ; 
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
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int /*<<< orphan*/  UART_DLL ; 
 int /*<<< orphan*/  UART_DLM ; 
 int /*<<< orphan*/  UART_FCR ; 
 unsigned char UART_FCR_ENABLE_FIFO ; 
 unsigned char UART_FCR_R_TRIG_10 ; 
 unsigned char UART_FCR_TRIGGER_1 ; 
 int /*<<< orphan*/  UART_IER ; 
 unsigned char UART_IER_MSI ; 
 int /*<<< orphan*/  UART_LCR ; 
 unsigned char UART_LCR_DLAB ; 
 unsigned char UART_LCR_EPAR ; 
 unsigned char UART_LCR_PARITY ; 
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
 int /*<<< orphan*/  sdio_out (struct sdio_uart_port*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  sdio_uart_write_mctrl (struct sdio_uart_port*,int /*<<< orphan*/ ) ; 
 unsigned int tty_termios_baud_rate (struct ktermios*) ; 

__attribute__((used)) static void sdio_uart_change_speed(struct sdio_uart_port *port,
				   struct ktermios *termios,
				   struct ktermios *old)
{
	unsigned char cval, fcr = 0;
	unsigned int baud, quot;

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

	for (;;) {
		baud = tty_termios_baud_rate(termios);
		if (baud == 0)
			baud = 9600;  /* Special case: B0 rate. */
		if (baud <= port->uartclk)
			break;
		/*
		 * Oops, the quotient was zero.  Try again with the old
		 * baud rate if possible, otherwise default to 9600.
		 */
		termios->c_cflag &= ~CBAUD;
		if (old) {
			termios->c_cflag |= old->c_cflag & CBAUD;
			old = NULL;
		} else
			termios->c_cflag |= B9600;
	}
	quot = (2 * port->uartclk + baud) / (2 * baud);

	if (baud < 2400)
		fcr = UART_FCR_ENABLE_FIFO | UART_FCR_TRIGGER_1;
	else
		fcr = UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10;

	port->read_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	if (termios->c_iflag & INPCK)
		port->read_status_mask |= UART_LSR_FE | UART_LSR_PE;
	if (termios->c_iflag & (BRKINT | PARMRK))
		port->read_status_mask |= UART_LSR_BI;

	/*
	 * Characters to ignore
	 */
	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask |= UART_LSR_PE | UART_LSR_FE;
	if (termios->c_iflag & IGNBRK) {
		port->ignore_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			port->ignore_status_mask |= UART_LSR_OE;
	}

	/*
	 * ignore all characters if CREAD is not set
	 */
	if ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= UART_LSR_DR;

	/*
	 * CTS flow control flag and modem status interrupts
	 */
	port->ier &= ~UART_IER_MSI;
	if ((termios->c_cflag & CRTSCTS) || !(termios->c_cflag & CLOCAL))
		port->ier |= UART_IER_MSI;

	port->lcr = cval;

	sdio_out(port, UART_IER, port->ier);
	sdio_out(port, UART_LCR, cval | UART_LCR_DLAB);
	sdio_out(port, UART_DLL, quot & 0xff);
	sdio_out(port, UART_DLM, quot >> 8);
	sdio_out(port, UART_LCR, cval);
	sdio_out(port, UART_FCR, fcr);

	sdio_uart_write_mctrl(port, port->mctrl);
}