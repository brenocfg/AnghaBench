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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct nouveau_fbdev {TYPE_2__ helper; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct nouveau_drm {TYPE_1__ client; struct nouveau_channel* channel; } ;
struct nouveau_channel {int accel_done; } ;
struct fb_info {scalar_t__ state; int flags; struct nouveau_fbdev* par; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 scalar_t__ FBINFO_STATE_RUNNING ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nouveau_channel_idle (struct nouveau_channel*) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_fbcon_gpu_lockup (struct fb_info*) ; 

__attribute__((used)) static int
nouveau_fbcon_sync(struct fb_info *info)
{
	struct nouveau_fbdev *fbcon = info->par;
	struct nouveau_drm *drm = nouveau_drm(fbcon->helper.dev);
	struct nouveau_channel *chan = drm->channel;
	int ret;

	if (!chan || !chan->accel_done || in_interrupt() ||
	    info->state != FBINFO_STATE_RUNNING ||
	    info->flags & FBINFO_HWACCEL_DISABLED)
		return 0;

	if (!mutex_trylock(&drm->client.mutex))
		return 0;

	ret = nouveau_channel_idle(chan);
	mutex_unlock(&drm->client.mutex);
	if (ret) {
		nouveau_fbcon_gpu_lockup(info);
		return 0;
	}

	chan->accel_done = false;
	return 0;
}