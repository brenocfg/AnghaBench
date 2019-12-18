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
struct ktermios {int /*<<< orphan*/  c_cflag; } ;
struct tty_struct {struct ktermios termios; } ;
struct serport {struct tty_struct* tty; } ;
struct serdev_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTSCTS ; 
 struct serport* serdev_controller_get_drvdata (struct serdev_controller*) ; 
 int /*<<< orphan*/  tty_set_termios (struct tty_struct*,struct ktermios*) ; 

__attribute__((used)) static void ttyport_set_flow_control(struct serdev_controller *ctrl, bool enable)
{
	struct serport *serport = serdev_controller_get_drvdata(ctrl);
	struct tty_struct *tty = serport->tty;
	struct ktermios ktermios = tty->termios;

	if (enable)
		ktermios.c_cflag |= CRTSCTS;
	else
		ktermios.c_cflag &= ~CRTSCTS;

	tty_set_termios(tty, &ktermios);
}