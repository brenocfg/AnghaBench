#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int handle; int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 TYPE_1__* bcare_ctl ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void sony_nc_battery_care_cleanup(struct platform_device *pd)
{
	if (bcare_ctl) {
		device_remove_file(&pd->dev, &bcare_ctl->attrs[0]);
		if (bcare_ctl->handle != 0x0115)
			device_remove_file(&pd->dev, &bcare_ctl->attrs[1]);

		kfree(bcare_ctl);
		bcare_ctl = NULL;
	}
}