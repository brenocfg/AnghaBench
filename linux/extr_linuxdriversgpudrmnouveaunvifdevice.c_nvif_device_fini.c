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
struct nvif_device {int /*<<< orphan*/  object; int /*<<< orphan*/ * runlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_object_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_user_fini (struct nvif_device*) ; 

void
nvif_device_fini(struct nvif_device *device)
{
	nvif_user_fini(device);
	kfree(device->runlist);
	device->runlist = NULL;
	nvif_object_fini(&device->object);
}