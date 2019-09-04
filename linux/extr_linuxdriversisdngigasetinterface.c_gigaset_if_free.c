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
struct cardstate {int /*<<< orphan*/  minor_index; int /*<<< orphan*/ * tty_dev; int /*<<< orphan*/  if_wake_tasklet; struct gigaset_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gigaset_if_free(struct cardstate *cs)
{
	struct gigaset_driver *drv;

	drv = cs->driver;
	if (!drv->have_tty)
		return;

	tasklet_disable(&cs->if_wake_tasklet);
	tasklet_kill(&cs->if_wake_tasklet);
	cs->tty_dev = NULL;
	tty_unregister_device(drv->tty, cs->minor_index);
}