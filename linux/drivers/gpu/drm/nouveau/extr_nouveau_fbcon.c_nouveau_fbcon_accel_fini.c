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
struct TYPE_4__ {TYPE_1__* fbdev; } ;
struct nouveau_fbdev {int /*<<< orphan*/  surf2d; int /*<<< orphan*/  clip; int /*<<< orphan*/  rop; int /*<<< orphan*/  patt; int /*<<< orphan*/  gdi; int /*<<< orphan*/  blit; int /*<<< orphan*/  twod; TYPE_2__ helper; } ;
struct nouveau_drm {scalar_t__ channel; struct nouveau_fbdev* fbcon; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBINFO_HWACCEL_DISABLED ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  nouveau_channel_idle (scalar_t__) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nvif_object_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nouveau_fbcon_accel_fini(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_fbdev *fbcon = drm->fbcon;
	if (fbcon && drm->channel) {
		console_lock();
		if (fbcon->helper.fbdev)
			fbcon->helper.fbdev->flags |= FBINFO_HWACCEL_DISABLED;
		console_unlock();
		nouveau_channel_idle(drm->channel);
		nvif_object_fini(&fbcon->twod);
		nvif_object_fini(&fbcon->blit);
		nvif_object_fini(&fbcon->gdi);
		nvif_object_fini(&fbcon->patt);
		nvif_object_fini(&fbcon->rop);
		nvif_object_fini(&fbcon->clip);
		nvif_object_fini(&fbcon->surf2d);
	}
}