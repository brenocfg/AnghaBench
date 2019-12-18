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
struct virtio_gpu_object {scalar_t__ dumb; } ;
struct TYPE_3__ {int /*<<< orphan*/ * obj; } ;
struct virtio_gpu_framebuffer {int /*<<< orphan*/  fence; TYPE_1__ base; } ;
struct virtio_gpu_device {int dummy; } ;
struct drm_plane_state {scalar_t__ fb; } ;
struct drm_plane {TYPE_2__* state; struct drm_device* dev; } ;
struct drm_device {struct virtio_gpu_device* dev_private; } ;
struct TYPE_4__ {scalar_t__ fb; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct virtio_gpu_object* gem_to_virtio_gpu_obj (int /*<<< orphan*/ ) ; 
 struct virtio_gpu_framebuffer* to_virtio_gpu_framebuffer (scalar_t__) ; 
 int /*<<< orphan*/  virtio_gpu_fence_alloc (struct virtio_gpu_device*) ; 

__attribute__((used)) static int virtio_gpu_cursor_prepare_fb(struct drm_plane *plane,
					struct drm_plane_state *new_state)
{
	struct drm_device *dev = plane->dev;
	struct virtio_gpu_device *vgdev = dev->dev_private;
	struct virtio_gpu_framebuffer *vgfb;
	struct virtio_gpu_object *bo;

	if (!new_state->fb)
		return 0;

	vgfb = to_virtio_gpu_framebuffer(new_state->fb);
	bo = gem_to_virtio_gpu_obj(vgfb->base.obj[0]);
	if (bo && bo->dumb && (plane->state->fb != new_state->fb)) {
		vgfb->fence = virtio_gpu_fence_alloc(vgdev);
		if (!vgfb->fence)
			return -ENOMEM;
	}

	return 0;
}