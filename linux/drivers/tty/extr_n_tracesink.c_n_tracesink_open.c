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
struct tty_struct {int /*<<< orphan*/ * disc_data; } ;

/* Variables and functions */
 int EEXIST ; 
 int EFAULT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * this_tty ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/ * tty_kref_get (struct tty_struct*) ; 
 int /*<<< orphan*/  writelock ; 

__attribute__((used)) static int n_tracesink_open(struct tty_struct *tty)
{
	int retval = -EEXIST;

	mutex_lock(&writelock);
	if (this_tty == NULL) {
		this_tty = tty_kref_get(tty);
		if (this_tty == NULL) {
			retval = -EFAULT;
		} else {
			tty->disc_data = this_tty;
			tty_driver_flush_buffer(tty);
			retval = 0;
		}
	}
	mutex_unlock(&writelock);

	return retval;
}