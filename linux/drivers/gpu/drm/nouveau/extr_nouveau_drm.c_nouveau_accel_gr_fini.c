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
struct nouveau_drm {int /*<<< orphan*/  channel; int /*<<< orphan*/  nvsw; int /*<<< orphan*/  notify; int /*<<< orphan*/  ntfy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_channel_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_channel_idle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvif_object_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_gpuobj_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nouveau_accel_gr_fini(struct nouveau_drm *drm)
{
	nouveau_channel_idle(drm->channel);
	nvif_object_fini(&drm->ntfy);
	nvkm_gpuobj_del(&drm->notify);
	nvif_object_fini(&drm->nvsw);
	nouveau_channel_del(&drm->channel);
}