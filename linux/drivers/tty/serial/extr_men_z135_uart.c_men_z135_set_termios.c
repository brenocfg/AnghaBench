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
typedef  int u8 ;
typedef  int u32 ;
struct uart_port {int /*<<< orphan*/  lock; scalar_t__ membase; } ;
struct men_z135_port {int automode; } ;
struct ktermios {int c_cflag; } ;

/* Variables and functions */
 int CLOCAL ; 
 int CMSPAR ; 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int LCR (int) ; 
 int MEN_Z135_BASECLK ; 
 scalar_t__ MEN_Z135_BAUD_REG ; 
 scalar_t__ MEN_Z135_CONF_REG ; 
 int MEN_Z135_IER_MSIEN ; 
 int MEN_Z135_LCR_SHIFT ; 
 int MEN_Z135_MCR_RCFC ; 
 int MEN_Z135_NSTB2 ; 
 int MEN_Z135_PAR_DIS ; 
 int MEN_Z135_PAR_ENA ; 
 int MEN_Z135_PEN_SHIFT ; 
 int MEN_Z135_PTY_EVN ; 
 int MEN_Z135_PTY_ODD ; 
 int MEN_Z135_PTY_SHIFT ; 
 int MEN_Z135_STB_SHIFT ; 
 scalar_t__ MEN_Z135_UART_FREQ ; 
 int MEN_Z135_WL5 ; 
 int MEN_Z135_WL6 ; 
 int MEN_Z135_WL7 ; 
 int MEN_Z135_WL8 ; 
 int PARENB ; 
 int PARODD ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct men_z135_port* to_men_z135 (struct uart_port*) ; 
 scalar_t__ tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,unsigned int,unsigned int) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void men_z135_set_termios(struct uart_port *port,
				struct ktermios *termios,
				struct ktermios *old)
{
	struct men_z135_port *uart = to_men_z135(port);
	unsigned int baud;
	u32 conf_reg;
	u32 bd_reg;
	u32 uart_freq;
	u8 lcr;

	conf_reg = ioread32(port->membase + MEN_Z135_CONF_REG);
	lcr = LCR(conf_reg);

	/* byte size */
	switch (termios->c_cflag & CSIZE) {
	case CS5:
		lcr |= MEN_Z135_WL5;
		break;
	case CS6:
		lcr |= MEN_Z135_WL6;
		break;
	case CS7:
		lcr |= MEN_Z135_WL7;
		break;
	case CS8:
		lcr |= MEN_Z135_WL8;
		break;
	}

	/* stop bits */
	if (termios->c_cflag & CSTOPB)
		lcr |= MEN_Z135_NSTB2 << MEN_Z135_STB_SHIFT;

	/* parity */
	if (termios->c_cflag & PARENB) {
		lcr |= MEN_Z135_PAR_ENA << MEN_Z135_PEN_SHIFT;

		if (termios->c_cflag & PARODD)
			lcr |= MEN_Z135_PTY_ODD << MEN_Z135_PTY_SHIFT;
		else
			lcr |= MEN_Z135_PTY_EVN << MEN_Z135_PTY_SHIFT;
	} else
		lcr |= MEN_Z135_PAR_DIS << MEN_Z135_PEN_SHIFT;

	conf_reg |= MEN_Z135_IER_MSIEN;
	if (termios->c_cflag & CRTSCTS) {
		conf_reg |= MEN_Z135_MCR_RCFC;
		uart->automode = true;
		termios->c_cflag &= ~CLOCAL;
	} else {
		conf_reg &= ~MEN_Z135_MCR_RCFC;
		uart->automode = false;
	}

	termios->c_cflag &= ~CMSPAR; /* Mark/Space parity is not supported */

	conf_reg |= lcr << MEN_Z135_LCR_SHIFT;
	iowrite32(conf_reg, port->membase + MEN_Z135_CONF_REG);

	uart_freq = ioread32(port->membase + MEN_Z135_UART_FREQ);
	if (uart_freq == 0)
		uart_freq = MEN_Z135_BASECLK;

	baud = uart_get_baud_rate(port, termios, old, 0, uart_freq / 16);

	spin_lock_irq(&port->lock);
	if (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);

	bd_reg = uart_freq / (4 * baud);
	iowrite32(bd_reg, port->membase + MEN_Z135_BAUD_REG);

	uart_update_timeout(port, termios->c_cflag, baud);
	spin_unlock_irq(&port->lock);
}