#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virtio_gpu_object {int dummy; } ;
struct TYPE_3__ {struct drm_gem_object** obj; } ;
struct virtio_gpu_framebuffer {scalar_t__ y2; scalar_t__ x2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; int /*<<< orphan*/  dirty_lock; TYPE_1__ base; } ;
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int drm_framebuffer_init (struct drm_device*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (struct drm_device*,TYPE_1__*,struct drm_mode_fb_cmd2 const*) ; 
 struct virtio_gpu_object* gem_to_virtio_gpu_obj (struct drm_gem_object*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_gpu_fb_funcs ; 

int
virtio_gpu_framebuffer_init(struct drm_device *dev,
			    struct virtio_gpu_framebuffer *vgfb,
			    const struct drm_mode_fb_cmd2 *mode_cmd,
			    struct drm_gem_object *obj)
{
	int ret;
	struct virtio_gpu_object *bo;

	vgfb->base.obj[0] = obj;

	bo = gem_to_virtio_gpu_obj(obj);

	drm_helper_mode_fill_fb_struct(dev, &vgfb->base, mode_cmd);

	ret = drm_framebuffer_init(dev, &vgfb->base, &virtio_gpu_fb_funcs);
	if (ret) {
		vgfb->base.obj[0] = NULL;
		return ret;
	}

	spin_lock_init(&vgfb->dirty_lock);
	vgfb->x1 = vgfb->y1 = INT_MAX;
	vgfb->x2 = vgfb->y2 = 0;
	return 0;
}