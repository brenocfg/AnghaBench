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
struct virtio_gpu_fbdev {int /*<<< orphan*/  work; int /*<<< orphan*/  vgfb; } ;
struct fb_info {struct virtio_gpu_fbdev* par; } ;
struct fb_copyarea {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_GPU_FBCON_POLL_PERIOD ; 
 int /*<<< orphan*/  drm_fb_helper_sys_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_gpu_dirty_update (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virtio_gpu_3d_copyarea(struct fb_info *info,
				   const struct fb_copyarea *area)
{
	struct virtio_gpu_fbdev *vfbdev = info->par;

	drm_fb_helper_sys_copyarea(info, area);
	virtio_gpu_dirty_update(&vfbdev->vgfb, true, area->dx, area->dy,
			   area->width, area->height);
	schedule_delayed_work(&vfbdev->work, VIRTIO_GPU_FBCON_POLL_PERIOD);
}