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
struct TYPE_2__ {scalar_t__ c_cflag; scalar_t__ c_ispeed; scalar_t__ c_ospeed; } ;
struct tty_struct {TYPE_1__ termios; scalar_t__ driver_data; } ;
struct ktermios {scalar_t__ c_cflag; scalar_t__ c_ispeed; scalar_t__ c_ospeed; } ;
typedef  int /*<<< orphan*/  modem_info ;

/* Variables and functions */
 int /*<<< orphan*/  isdn_tty_change_speed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modem_info_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isdn_tty_set_termios(struct tty_struct *tty, struct ktermios *old_termios)
{
	modem_info *info = (modem_info *) tty->driver_data;

	mutex_lock(&modem_info_mutex);
	if (!old_termios)
		isdn_tty_change_speed(info);
	else {
		if (tty->termios.c_cflag == old_termios->c_cflag &&
		    tty->termios.c_ispeed == old_termios->c_ispeed &&
		    tty->termios.c_ospeed == old_termios->c_ospeed) {
			mutex_unlock(&modem_info_mutex);
			return;
		}
		isdn_tty_change_speed(info);
	}
	mutex_unlock(&modem_info_mutex);
}