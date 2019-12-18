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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct serio {TYPE_1__ dev; } ;
struct atkbd {int /*<<< orphan*/  event_work; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atkbd_attribute_group ; 
 int /*<<< orphan*/  atkbd_disable (struct atkbd*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct atkbd*) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct atkbd* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atkbd_disconnect(struct serio *serio)
{
	struct atkbd *atkbd = serio_get_drvdata(serio);

	sysfs_remove_group(&serio->dev.kobj, &atkbd_attribute_group);

	atkbd_disable(atkbd);

	input_unregister_device(atkbd->dev);

	/*
	 * Make sure we don't have a command in flight.
	 * Note that since atkbd->enabled is false event work will keep
	 * rescheduling itself until it gets canceled and will not try
	 * accessing freed input device or serio port.
	 */
	cancel_delayed_work_sync(&atkbd->event_work);

	serio_close(serio);
	serio_set_drvdata(serio, NULL);
	kfree(atkbd);
}