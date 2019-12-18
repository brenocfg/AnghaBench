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
struct tty_struct {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  TTY_LDISC_HALTED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __tty_ldisc_lock (struct tty_struct*,unsigned long) ; 
 int __tty_ldisc_lock_nested (struct tty_struct*,unsigned long) ; 
 int /*<<< orphan*/  __tty_ldisc_unlock (struct tty_struct*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tty_ldisc_lock_pair_timeout(struct tty_struct *tty, struct tty_struct *tty2,
			    unsigned long timeout)
{
	int ret;

	if (tty < tty2) {
		ret = __tty_ldisc_lock(tty, timeout);
		if (ret) {
			ret = __tty_ldisc_lock_nested(tty2, timeout);
			if (!ret)
				__tty_ldisc_unlock(tty);
		}
	} else {
		/* if this is possible, it has lots of implications */
		WARN_ON_ONCE(tty == tty2);
		if (tty2 && tty != tty2) {
			ret = __tty_ldisc_lock(tty2, timeout);
			if (ret) {
				ret = __tty_ldisc_lock_nested(tty, timeout);
				if (!ret)
					__tty_ldisc_unlock(tty2);
			}
		} else
			ret = __tty_ldisc_lock(tty, timeout);
	}

	if (!ret)
		return -EBUSY;

	set_bit(TTY_LDISC_HALTED, &tty->flags);
	if (tty2)
		set_bit(TTY_LDISC_HALTED, &tty2->flags);
	return 0;
}