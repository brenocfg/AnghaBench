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
typedef  int upf_t ;
struct uart_port {int flags; } ;
struct ktermios {int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBAUD ; 
#define  UPF_SPD_HI 131 
 int UPF_SPD_MASK ; 
#define  UPF_SPD_SHI 130 
#define  UPF_SPD_VHI 129 
#define  UPF_SPD_WARP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,unsigned int,unsigned int) ; 

unsigned int
uart_get_baud_rate(struct uart_port *port, struct ktermios *termios,
		   struct ktermios *old, unsigned int min, unsigned int max)
{
	unsigned int try;
	unsigned int baud;
	unsigned int altbaud;
	int hung_up = 0;
	upf_t flags = port->flags & UPF_SPD_MASK;

	switch (flags) {
	case UPF_SPD_HI:
		altbaud = 57600;
		break;
	case UPF_SPD_VHI:
		altbaud = 115200;
		break;
	case UPF_SPD_SHI:
		altbaud = 230400;
		break;
	case UPF_SPD_WARP:
		altbaud = 460800;
		break;
	default:
		altbaud = 38400;
		break;
	}

	for (try = 0; try < 2; try++) {
		baud = tty_termios_baud_rate(termios);

		/*
		 * The spd_hi, spd_vhi, spd_shi, spd_warp kludge...
		 * Die! Die! Die!
		 */
		if (try == 0 && baud == 38400)
			baud = altbaud;

		/*
		 * Special case: B0 rate.
		 */
		if (baud == 0) {
			hung_up = 1;
			baud = 9600;
		}

		if (baud >= min && baud <= max)
			return baud;

		/*
		 * Oops, the quotient was zero.  Try again with
		 * the old baud rate if possible.
		 */
		termios->c_cflag &= ~CBAUD;
		if (old) {
			baud = tty_termios_baud_rate(old);
			if (!hung_up)
				tty_termios_encode_baud_rate(termios,
								baud, baud);
			old = NULL;
			continue;
		}

		/*
		 * As a last resort, if the range cannot be met then clip to
		 * the nearest chip supported rate.
		 */
		if (!hung_up) {
			if (baud <= min)
				tty_termios_encode_baud_rate(termios,
							min + 1, min + 1);
			else
				tty_termios_encode_baud_rate(termios,
							max - 1, max - 1);
		}
	}
	/* Should never happen */
	WARN_ON(1);
	return 0;
}