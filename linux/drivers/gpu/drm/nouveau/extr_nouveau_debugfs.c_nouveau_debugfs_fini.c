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
struct nouveau_drm {TYPE_2__* debugfs; } ;
struct TYPE_3__ {scalar_t__ priv; } ;
struct TYPE_4__ {TYPE_1__ ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  nvif_object_fini (TYPE_1__*) ; 

void
nouveau_debugfs_fini(struct nouveau_drm *drm)
{
	if (drm->debugfs && drm->debugfs->ctrl.priv)
		nvif_object_fini(&drm->debugfs->ctrl);

	kfree(drm->debugfs);
	drm->debugfs = NULL;
}