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
struct TYPE_2__ {int /*<<< orphan*/ * func; int /*<<< orphan*/  object; } ;
struct nvif_device {TYPE_1__ user; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvif_object_fini (int /*<<< orphan*/ *) ; 

void
nvif_user_fini(struct nvif_device *device)
{
	if (device->user.func) {
		nvif_object_fini(&device->user.object);
		device->user.func = NULL;
	}
}