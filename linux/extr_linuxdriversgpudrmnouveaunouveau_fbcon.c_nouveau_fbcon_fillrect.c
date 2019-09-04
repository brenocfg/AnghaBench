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
struct TYPE_5__ {scalar_t__ family; } ;
struct nvif_device {TYPE_2__ info; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct nouveau_fbdev {TYPE_1__ helper; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; struct nvif_device device; } ;
struct nouveau_drm {TYPE_3__ client; } ;
struct fb_info {scalar_t__ state; int flags; struct nouveau_fbdev* par; } ;
struct fb_fillrect {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int FBINFO_HWACCEL_DISABLED ; 
 scalar_t__ FBINFO_STATE_RUNNING ; 
 scalar_t__ NV_DEVICE_INFO_V0_FERMI ; 
 scalar_t__ NV_DEVICE_INFO_V0_TESLA ; 
 int /*<<< orphan*/  drm_fb_helper_cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_fbcon_gpu_lockup (struct fb_info*) ; 
 int nv04_fbcon_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int nv50_fbcon_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int nvc0_fbcon_fillrect (struct fb_info*,struct fb_fillrect const*) ; 

__attribute__((used)) static void
nouveau_fbcon_fillrect(struct fb_info *info, const struct fb_fillrect *rect)
{
	struct nouveau_fbdev *fbcon = info->par;
	struct nouveau_drm *drm = nouveau_drm(fbcon->helper.dev);
	struct nvif_device *device = &drm->client.device;
	int ret;

	if (info->state != FBINFO_STATE_RUNNING)
		return;

	ret = -ENODEV;
	if (!in_interrupt() && !(info->flags & FBINFO_HWACCEL_DISABLED) &&
	    mutex_trylock(&drm->client.mutex)) {
		if (device->info.family < NV_DEVICE_INFO_V0_TESLA)
			ret = nv04_fbcon_fillrect(info, rect);
		else
		if (device->info.family < NV_DEVICE_INFO_V0_FERMI)
			ret = nv50_fbcon_fillrect(info, rect);
		else
			ret = nvc0_fbcon_fillrect(info, rect);
		mutex_unlock(&drm->client.mutex);
	}

	if (ret == 0)
		return;

	if (ret != -ENODEV)
		nouveau_fbcon_gpu_lockup(info);
	drm_fb_helper_cfb_fillrect(info, rect);
}