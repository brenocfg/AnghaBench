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
struct TYPE_5__ {int /*<<< orphan*/  base; } ;
struct nouveau_drm {scalar_t__ fence; TYPE_2__ master; } ;
struct TYPE_4__ {scalar_t__ num_crtc; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* resume ) (struct nouveau_drm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,int) ; 
 int /*<<< orphan*/  nouveau_display_resume (struct drm_device*,int) ; 
 int /*<<< orphan*/  nouveau_dmem_resume (struct nouveau_drm*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_fbcon_set_suspend (struct drm_device*,int /*<<< orphan*/ ) ; 
 TYPE_3__* nouveau_fence (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nouveau_led_resume (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_run_vbios_init (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_svm_resume (struct nouveau_drm*) ; 
 int nvif_client_resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_drm*) ; 

__attribute__((used)) static int
nouveau_do_resume(struct drm_device *dev, bool runtime)
{
	int ret = 0;
	struct nouveau_drm *drm = nouveau_drm(dev);

	NV_DEBUG(drm, "resuming object tree...\n");
	ret = nvif_client_resume(&drm->master.base);
	if (ret) {
		NV_ERROR(drm, "Client resume failed with error: %d\n", ret);
		return ret;
	}

	NV_DEBUG(drm, "resuming fence...\n");
	if (drm->fence && nouveau_fence(drm)->resume)
		nouveau_fence(drm)->resume(drm);

	nouveau_run_vbios_init(dev);

	if (dev->mode_config.num_crtc) {
		NV_DEBUG(drm, "resuming display...\n");
		nouveau_display_resume(dev, runtime);
		NV_DEBUG(drm, "resuming console...\n");
		nouveau_fbcon_set_suspend(dev, 0);
	}

	nouveau_led_resume(dev);
	nouveau_dmem_resume(drm);
	nouveau_svm_resume(drm);
	return 0;
}