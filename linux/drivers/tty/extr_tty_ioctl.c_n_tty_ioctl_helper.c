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
struct tty_struct {int flow_stopped; int /*<<< orphan*/  flow_lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  START_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  STOP_CHAR (struct tty_struct*) ; 
#define  TCFLSH 133 
#define  TCIOFF 132 
#define  TCION 131 
#define  TCOOFF 130 
#define  TCOON 129 
#define  TCXONC 128 
 int /*<<< orphan*/  __DISABLED_CHAR ; 
 int /*<<< orphan*/  __start_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  __stop_tty (struct tty_struct*) ; 
 int __tty_perform_flush (struct tty_struct*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int tty_check_change (struct tty_struct*) ; 
 int tty_mode_ioctl (struct tty_struct*,struct file*,unsigned int,unsigned long) ; 
 int tty_send_xchar (struct tty_struct*,int /*<<< orphan*/ ) ; 

int n_tty_ioctl_helper(struct tty_struct *tty, struct file *file,
		       unsigned int cmd, unsigned long arg)
{
	int retval;

	switch (cmd) {
	case TCXONC:
		retval = tty_check_change(tty);
		if (retval)
			return retval;
		switch (arg) {
		case TCOOFF:
			spin_lock_irq(&tty->flow_lock);
			if (!tty->flow_stopped) {
				tty->flow_stopped = 1;
				__stop_tty(tty);
			}
			spin_unlock_irq(&tty->flow_lock);
			break;
		case TCOON:
			spin_lock_irq(&tty->flow_lock);
			if (tty->flow_stopped) {
				tty->flow_stopped = 0;
				__start_tty(tty);
			}
			spin_unlock_irq(&tty->flow_lock);
			break;
		case TCIOFF:
			if (STOP_CHAR(tty) != __DISABLED_CHAR)
				retval = tty_send_xchar(tty, STOP_CHAR(tty));
			break;
		case TCION:
			if (START_CHAR(tty) != __DISABLED_CHAR)
				retval = tty_send_xchar(tty, START_CHAR(tty));
			break;
		default:
			return -EINVAL;
		}
		return retval;
	case TCFLSH:
		retval = tty_check_change(tty);
		if (retval)
			return retval;
		return __tty_perform_flush(tty, arg);
	default:
		/* Try the mode commands */
		return tty_mode_ioctl(tty, file, cmd, arg);
	}
}