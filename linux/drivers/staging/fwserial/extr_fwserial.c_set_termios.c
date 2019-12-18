#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int c_lflag; int /*<<< orphan*/  c_oflag; } ;
struct tty_struct {TYPE_1__ termios; } ;
struct fwtty_port {unsigned int cps; int write_only; scalar_t__ loopback; int /*<<< orphan*/  ignore_mask; int /*<<< orphan*/  status_mask; } ;

/* Variables and functions */
 int BRKINT ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int /*<<< orphan*/  C_CREAD (struct tty_struct*) ; 
 int C_CSIZE (struct tty_struct*) ; 
 scalar_t__ C_CSTOPB (struct tty_struct*) ; 
 scalar_t__ C_PARENB (struct tty_struct*) ; 
 int ECHO ; 
 int ECHOCTL ; 
 int ECHOE ; 
 int ECHOK ; 
 int ECHOKE ; 
 int ECHONL ; 
 int ECHOPRT ; 
 scalar_t__ I_IGNBRK (struct tty_struct*) ; 
 scalar_t__ I_IGNPAR (struct tty_struct*) ; 
 int /*<<< orphan*/  ONLCR ; 
 int PARMRK ; 
 int /*<<< orphan*/  UART_LSR_BI ; 
 int /*<<< orphan*/  UART_LSR_OE ; 
 scalar_t__ _I_FLAG (struct tty_struct*,int) ; 
 unsigned int tty_termios_baud_rate (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (TYPE_1__*,unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int set_termios(struct fwtty_port *port, struct tty_struct *tty)
{
	unsigned int baud, frame;

	baud = tty_termios_baud_rate(&tty->termios);
	tty_termios_encode_baud_rate(&tty->termios, baud, baud);

	/* compute bit count of 2 frames */
	frame = 12 + ((C_CSTOPB(tty)) ? 4 : 2) + ((C_PARENB(tty)) ? 2 : 0);

	switch (C_CSIZE(tty)) {
	case CS5:
		frame -= (C_CSTOPB(tty)) ? 1 : 0;
		break;
	case CS6:
		frame += 2;
		break;
	case CS7:
		frame += 4;
		break;
	case CS8:
		frame += 6;
		break;
	}

	port->cps = (baud << 1) / frame;

	port->status_mask = UART_LSR_OE;
	if (_I_FLAG(tty, BRKINT | PARMRK))
		port->status_mask |= UART_LSR_BI;

	port->ignore_mask = 0;
	if (I_IGNBRK(tty)) {
		port->ignore_mask |= UART_LSR_BI;
		if (I_IGNPAR(tty))
			port->ignore_mask |= UART_LSR_OE;
	}

	port->write_only = !C_CREAD(tty);

	/* turn off echo and newline xlat if loopback */
	if (port->loopback) {
		tty->termios.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHOKE |
					  ECHONL | ECHOPRT | ECHOCTL);
		tty->termios.c_oflag &= ~ONLCR;
	}

	return baud;
}