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
struct tty_struct {size_t index; struct gdm* driver_data; TYPE_1__* driver; } ;
struct tty_driver {int dummy; } ;
struct gdm {int /*<<< orphan*/  port; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_STRING ; 
 int ENODEV ; 
 int /*<<< orphan*/  TTY_MAX_COUNT ; 
 struct gdm*** gdm_table ; 
 int /*<<< orphan*/  gdm_table_lock ; 
 int match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_put (int /*<<< orphan*/ *) ; 
 int tty_standard_install (struct tty_driver*,struct tty_struct*) ; 

__attribute__((used)) static int gdm_tty_install(struct tty_driver *driver, struct tty_struct *tty)
{
	struct gdm *gdm = NULL;
	int ret;

	ret = match_string(DRIVER_STRING, TTY_MAX_COUNT,
			   tty->driver->driver_name);
	if (ret < 0)
		return -ENODEV;

	mutex_lock(&gdm_table_lock);
	gdm = gdm_table[ret][tty->index];
	if (!gdm) {
		mutex_unlock(&gdm_table_lock);
		return -ENODEV;
	}

	tty_port_get(&gdm->port);

	ret = tty_standard_install(driver, tty);
	if (ret) {
		tty_port_put(&gdm->port);
		mutex_unlock(&gdm_table_lock);
		return ret;
	}

	tty->driver_data = gdm;
	mutex_unlock(&gdm_table_lock);

	return 0;
}