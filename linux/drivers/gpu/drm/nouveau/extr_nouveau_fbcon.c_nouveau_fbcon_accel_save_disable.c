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
struct nouveau_drm {TYPE_2__* fbcon; } ;
struct drm_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_3__* fbdev; } ;
struct TYPE_5__ {TYPE_1__ helper; int /*<<< orphan*/  saved_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBINFO_HWACCEL_DISABLED ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 

void
nouveau_fbcon_accel_save_disable(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	if (drm->fbcon && drm->fbcon->helper.fbdev) {
		drm->fbcon->saved_flags = drm->fbcon->helper.fbdev->flags;
		drm->fbcon->helper.fbdev->flags |= FBINFO_HWACCEL_DISABLED;
	}
}