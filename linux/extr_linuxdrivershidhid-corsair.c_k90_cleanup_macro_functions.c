#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct k90_drvdata* name; } ;
struct TYPE_5__ {int removed; TYPE_3__ cdev; int /*<<< orphan*/  work; } ;
struct k90_drvdata {TYPE_2__ record_led; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct hid_device {TYPE_1__ dev; } ;
struct corsair_drvdata {struct k90_drvdata* k90; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct corsair_drvdata* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  k90_attr_group ; 
 int /*<<< orphan*/  kfree (struct k90_drvdata*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_3__*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void k90_cleanup_macro_functions(struct hid_device *dev)
{
	struct corsair_drvdata *drvdata = hid_get_drvdata(dev);
	struct k90_drvdata *k90 = drvdata->k90;

	if (k90) {
		sysfs_remove_group(&dev->dev.kobj, &k90_attr_group);

		k90->record_led.removed = true;
		led_classdev_unregister(&k90->record_led.cdev);
		cancel_work_sync(&k90->record_led.work);
		kfree(k90->record_led.cdev.name);

		kfree(k90);
	}
}