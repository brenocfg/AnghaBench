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
struct TYPE_3__ {int /*<<< orphan*/  mode_attr; int /*<<< orphan*/  profiles_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* th_handle ; 

__attribute__((used)) static void sony_nc_thermal_cleanup(struct platform_device *pd)
{
	if (th_handle) {
		device_remove_file(&pd->dev, &th_handle->profiles_attr);
		device_remove_file(&pd->dev, &th_handle->mode_attr);
		kfree(th_handle);
		th_handle = NULL;
	}
}