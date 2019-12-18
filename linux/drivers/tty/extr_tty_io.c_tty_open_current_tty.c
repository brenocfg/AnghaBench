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
struct tty_struct {int dummy; } ;
struct file {int /*<<< orphan*/  f_flags; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int ENXIO ; 
 struct tty_struct* ERR_PTR (int) ; 
 scalar_t__ MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  TTYAUX_MAJOR ; 
 struct tty_struct* get_current_tty () ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_lock (struct tty_struct*) ; 
 int tty_reopen (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty_struct*) ; 

__attribute__((used)) static struct tty_struct *tty_open_current_tty(dev_t device, struct file *filp)
{
	struct tty_struct *tty;
	int retval;

	if (device != MKDEV(TTYAUX_MAJOR, 0))
		return NULL;

	tty = get_current_tty();
	if (!tty)
		return ERR_PTR(-ENXIO);

	filp->f_flags |= O_NONBLOCK; /* Don't let /dev/tty block */
	/* noctty = 1; */
	tty_lock(tty);
	tty_kref_put(tty);	/* safe to drop the kref now */

	retval = tty_reopen(tty);
	if (retval < 0) {
		tty_unlock(tty);
		tty = ERR_PTR(retval);
	}
	return tty;
}