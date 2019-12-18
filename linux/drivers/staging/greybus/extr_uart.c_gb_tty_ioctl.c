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
struct tty_struct {struct gb_tty* driver_data; } ;
struct gb_tty {int dummy; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
#define  TIOCMIWAIT 128 
 int wait_serial_change (struct gb_tty*,unsigned long) ; 

__attribute__((used)) static int gb_tty_ioctl(struct tty_struct *tty, unsigned int cmd,
			unsigned long arg)
{
	struct gb_tty *gb_tty = tty->driver_data;

	switch (cmd) {
	case TIOCMIWAIT:
		return wait_serial_change(gb_tty, arg);
	}

	return -ENOIOCTLCMD;
}