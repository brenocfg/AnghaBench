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
struct TYPE_4__ {int /*<<< orphan*/  object; } ;
struct TYPE_5__ {TYPE_1__ device; } ;
struct nouveau_drm {TYPE_3__* debugfs; TYPE_2__ client; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVIF_CLASS_CONTROL ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvif_object_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
nouveau_debugfs_init(struct nouveau_drm *drm)
{
	int ret;

	drm->debugfs = kzalloc(sizeof(*drm->debugfs), GFP_KERNEL);
	if (!drm->debugfs)
		return -ENOMEM;

	ret = nvif_object_init(&drm->client.device.object, 0,
			       NVIF_CLASS_CONTROL, NULL, 0,
			       &drm->debugfs->ctrl);
	if (ret)
		return ret;

	return 0;
}