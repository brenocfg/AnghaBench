#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_1__ attr; } ;
struct TYPE_6__ {TYPE_4__* attrs; } ;

/* Variables and functions */
 int LID_RESUME_MAX ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* lid_ctl ; 

__attribute__((used)) static void sony_nc_lid_resume_cleanup(struct platform_device *pd)
{
	int i;

	if (lid_ctl) {
		for (i = 0; i < LID_RESUME_MAX; i++) {
			if (!lid_ctl->attrs[i].attr.name)
				break;

			device_remove_file(&pd->dev, &lid_ctl->attrs[i]);
		}

		kfree(lid_ctl);
		lid_ctl = NULL;
	}
}