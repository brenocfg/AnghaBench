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
struct ktermios {int c_cflag; } ;
struct tty_struct {struct ktermios termios; } ;
struct serport {struct tty_struct* tty; } ;
struct serdev_controller {int dummy; } ;
typedef  enum serdev_parity { ____Placeholder_serdev_parity } serdev_parity ;

/* Variables and functions */
 int CMSPAR ; 
 int EINVAL ; 
 int PARENB ; 
 int PARODD ; 
 int SERDEV_PARITY_NONE ; 
 int SERDEV_PARITY_ODD ; 
 struct serport* serdev_controller_get_drvdata (struct serdev_controller*) ; 
 int /*<<< orphan*/  tty_set_termios (struct tty_struct*,struct ktermios*) ; 

__attribute__((used)) static int ttyport_set_parity(struct serdev_controller *ctrl,
			      enum serdev_parity parity)
{
	struct serport *serport = serdev_controller_get_drvdata(ctrl);
	struct tty_struct *tty = serport->tty;
	struct ktermios ktermios = tty->termios;

	ktermios.c_cflag &= ~(PARENB | PARODD | CMSPAR);
	if (parity != SERDEV_PARITY_NONE) {
		ktermios.c_cflag |= PARENB;
		if (parity == SERDEV_PARITY_ODD)
			ktermios.c_cflag |= PARODD;
	}

	tty_set_termios(tty, &ktermios);

	if ((tty->termios.c_cflag & (PARENB | PARODD | CMSPAR)) !=
	    (ktermios.c_cflag & (PARENB | PARODD | CMSPAR)))
		return -EINVAL;

	return 0;
}