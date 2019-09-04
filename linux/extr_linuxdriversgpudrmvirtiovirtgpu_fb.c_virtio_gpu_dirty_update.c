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
typedef  int uint32_t ;
struct virtio_gpu_object {int /*<<< orphan*/  hw_res_handle; } ;
struct TYPE_4__ {int width; int height; int* pitches; int /*<<< orphan*/ * obj; TYPE_1__* format; struct drm_device* dev; } ;
struct virtio_gpu_framebuffer {int y1; int y2; int x1; int x2; TYPE_2__ base; int /*<<< orphan*/  dirty_lock; } ;
struct virtio_gpu_device {int dummy; } ;
struct drm_device {struct virtio_gpu_device* dev_private; } ;
struct TYPE_3__ {int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int,int,int,int,int) ; 
 int EINVAL ; 
 int INT_MAX ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 struct virtio_gpu_object* gem_to_virtio_gpu_obj (int /*<<< orphan*/ ) ; 
 scalar_t__ in_atomic () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virtio_gpu_cmd_resource_flush (struct virtio_gpu_device*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  virtio_gpu_cmd_transfer_to_host_2d (struct virtio_gpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int virtio_gpu_dirty_update(struct virtio_gpu_framebuffer *fb,
				   bool store, int x, int y,
				   int width, int height)
{
	struct drm_device *dev = fb->base.dev;
	struct virtio_gpu_device *vgdev = dev->dev_private;
	bool store_for_later = false;
	int bpp = fb->base.format->cpp[0];
	int x2, y2;
	unsigned long flags;
	struct virtio_gpu_object *obj = gem_to_virtio_gpu_obj(fb->base.obj[0]);

	if ((width <= 0) ||
	    (x + width > fb->base.width) ||
	    (y + height > fb->base.height)) {
		DRM_DEBUG("values out of range %dx%d+%d+%d, fb %dx%d\n",
			  width, height, x, y,
			  fb->base.width, fb->base.height);
		return -EINVAL;
	}

	/*
	 * Can be called with pretty much any context (console output
	 * path).  If we are in atomic just store the dirty rect info
	 * to send out the update later.
	 *
	 * Can't test inside spin lock.
	 */
	if (in_atomic() || store)
		store_for_later = true;

	x2 = x + width - 1;
	y2 = y + height - 1;

	spin_lock_irqsave(&fb->dirty_lock, flags);

	if (fb->y1 < y)
		y = fb->y1;
	if (fb->y2 > y2)
		y2 = fb->y2;
	if (fb->x1 < x)
		x = fb->x1;
	if (fb->x2 > x2)
		x2 = fb->x2;

	if (store_for_later) {
		fb->x1 = x;
		fb->x2 = x2;
		fb->y1 = y;
		fb->y2 = y2;
		spin_unlock_irqrestore(&fb->dirty_lock, flags);
		return 0;
	}

	fb->x1 = fb->y1 = INT_MAX;
	fb->x2 = fb->y2 = 0;

	spin_unlock_irqrestore(&fb->dirty_lock, flags);

	{
		uint32_t offset;
		uint32_t w = x2 - x + 1;
		uint32_t h = y2 - y + 1;

		offset = (y * fb->base.pitches[0]) + x * bpp;

		virtio_gpu_cmd_transfer_to_host_2d(vgdev, obj->hw_res_handle,
						   offset,
						   cpu_to_le32(w),
						   cpu_to_le32(h),
						   cpu_to_le32(x),
						   cpu_to_le32(y),
						   NULL);

	}
	virtio_gpu_cmd_resource_flush(vgdev, obj->hw_res_handle,
				      x, y, x2 - x + 1, y2 - y + 1);
	return 0;
}