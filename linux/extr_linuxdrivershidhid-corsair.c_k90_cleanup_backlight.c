#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hid_device {int dummy; } ;
struct corsair_drvdata {TYPE_2__* backlight; } ;
struct TYPE_3__ {TYPE_2__* name; } ;
struct TYPE_4__ {int removed; TYPE_1__ cdev; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct corsair_drvdata* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 

__attribute__((used)) static void k90_cleanup_backlight(struct hid_device *dev)
{
	struct corsair_drvdata *drvdata = hid_get_drvdata(dev);

	if (drvdata->backlight) {
		drvdata->backlight->removed = true;
		led_classdev_unregister(&drvdata->backlight->cdev);
		cancel_work_sync(&drvdata->backlight->work);
		kfree(drvdata->backlight->cdev.name);
		kfree(drvdata->backlight);
	}
}