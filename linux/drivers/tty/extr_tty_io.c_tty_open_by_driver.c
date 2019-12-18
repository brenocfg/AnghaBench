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
struct tty_struct {int /*<<< orphan*/  port; } ;
struct tty_driver {int /*<<< orphan*/  port; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINTR ; 
 int ERESTARTSYS ; 
 struct tty_struct* ERR_CAST (struct tty_struct*) ; 
 struct tty_struct* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct tty_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_driver_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_driver_lookup_tty (struct tty_struct*,struct file*,int) ; 
 struct tty_struct* tty_init_dev (struct tty_struct*,int) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int tty_lock_interruptible (struct tty_struct*) ; 
 struct tty_struct* tty_lookup_driver (int /*<<< orphan*/ ,struct file*,int*) ; 
 int /*<<< orphan*/  tty_mutex ; 
 scalar_t__ tty_port_kopened (int /*<<< orphan*/ ) ; 
 int tty_reopen (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty_struct*) ; 

__attribute__((used)) static struct tty_struct *tty_open_by_driver(dev_t device, struct inode *inode,
					     struct file *filp)
{
	struct tty_struct *tty;
	struct tty_driver *driver = NULL;
	int index = -1;
	int retval;

	mutex_lock(&tty_mutex);
	driver = tty_lookup_driver(device, filp, &index);
	if (IS_ERR(driver)) {
		mutex_unlock(&tty_mutex);
		return ERR_CAST(driver);
	}

	/* check whether we're reopening an existing tty */
	tty = tty_driver_lookup_tty(driver, filp, index);
	if (IS_ERR(tty)) {
		mutex_unlock(&tty_mutex);
		goto out;
	}

	if (tty) {
		if (tty_port_kopened(tty->port)) {
			tty_kref_put(tty);
			mutex_unlock(&tty_mutex);
			tty = ERR_PTR(-EBUSY);
			goto out;
		}
		mutex_unlock(&tty_mutex);
		retval = tty_lock_interruptible(tty);
		tty_kref_put(tty);  /* drop kref from tty_driver_lookup_tty() */
		if (retval) {
			if (retval == -EINTR)
				retval = -ERESTARTSYS;
			tty = ERR_PTR(retval);
			goto out;
		}
		retval = tty_reopen(tty);
		if (retval < 0) {
			tty_unlock(tty);
			tty = ERR_PTR(retval);
		}
	} else { /* Returns with the tty_lock held for now */
		tty = tty_init_dev(driver, index);
		mutex_unlock(&tty_mutex);
	}
out:
	tty_driver_kref_put(driver);
	return tty;
}