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
struct TYPE_3__ {int /*<<< orphan*/  devattr; } ;

/* Variables and functions */
 scalar_t__ debug ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* handles ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static int sony_nc_handles_cleanup(struct platform_device *pd)
{
	if (handles) {
		if (debug)
			device_remove_file(&pd->dev, &handles->devattr);
		kfree(handles);
		handles = NULL;
	}
	return 0;
}