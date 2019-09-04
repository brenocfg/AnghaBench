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
struct TYPE_3__ {int /*<<< orphan*/  copy; } ;
struct nouveau_drm {scalar_t__ fence; int /*<<< orphan*/  cechan; TYPE_1__ ttm; int /*<<< orphan*/  channel; int /*<<< orphan*/  nvsw; int /*<<< orphan*/  flip; int /*<<< orphan*/  notify; int /*<<< orphan*/  ntfy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dtor ) (struct nouveau_drm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_channel_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_channel_idle (int /*<<< orphan*/ ) ; 
 TYPE_2__* nouveau_fence (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nvif_notify_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_object_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_gpuobj_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_drm*) ; 

__attribute__((used)) static void
nouveau_accel_fini(struct nouveau_drm *drm)
{
	nouveau_channel_idle(drm->channel);
	nvif_object_fini(&drm->ntfy);
	nvkm_gpuobj_del(&drm->notify);
	nvif_notify_fini(&drm->flip);
	nvif_object_fini(&drm->nvsw);
	nouveau_channel_del(&drm->channel);

	nouveau_channel_idle(drm->cechan);
	nvif_object_fini(&drm->ttm.copy);
	nouveau_channel_del(&drm->cechan);

	if (drm->fence)
		nouveau_fence(drm)->dtor(drm);
}