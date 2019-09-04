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
struct gigaset_driver {int /*<<< orphan*/  tty; int /*<<< orphan*/  have_tty; } ;
struct cardstate {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * tty_dev; int /*<<< orphan*/  minor_index; int /*<<< orphan*/  port; int /*<<< orphan*/  if_wake_tasklet; struct gigaset_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct cardstate*) ; 
 int /*<<< orphan*/  if_wake ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/ * tty_port_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gigaset_if_init(struct cardstate *cs)
{
	struct gigaset_driver *drv;

	drv = cs->driver;
	if (!drv->have_tty)
		return;

	tasklet_init(&cs->if_wake_tasklet, if_wake, (unsigned long) cs);

	mutex_lock(&cs->mutex);
	cs->tty_dev = tty_port_register_device(&cs->port, drv->tty,
			cs->minor_index, NULL);

	if (!IS_ERR(cs->tty_dev))
		dev_set_drvdata(cs->tty_dev, cs);
	else {
		pr_warning("could not register device to the tty subsystem\n");
		cs->tty_dev = NULL;
	}
	mutex_unlock(&cs->mutex);
}