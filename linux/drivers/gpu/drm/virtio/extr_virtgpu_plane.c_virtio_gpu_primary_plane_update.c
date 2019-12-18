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
typedef  scalar_t__ uint32_t ;
struct virtio_gpu_output {int /*<<< orphan*/  index; scalar_t__ enabled; } ;
struct virtio_gpu_object {scalar_t__ dumb; scalar_t__ hw_res_handle; } ;
struct TYPE_3__ {int /*<<< orphan*/ * obj; } ;
struct virtio_gpu_framebuffer {TYPE_1__ base; } ;
struct virtio_gpu_device {int dummy; } ;
struct drm_plane_state {scalar_t__ crtc; } ;
struct drm_plane {TYPE_2__* state; struct drm_device* dev; } ;
struct drm_device {struct virtio_gpu_device* dev_private; } ;
struct TYPE_4__ {int src_w; int src_h; int src_x; int src_y; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; int /*<<< orphan*/  crtc_h; int /*<<< orphan*/  crtc_w; scalar_t__ fb; scalar_t__ crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 struct virtio_gpu_output* drm_crtc_to_virtio_gpu_output (scalar_t__) ; 
 struct virtio_gpu_object* gem_to_virtio_gpu_obj (int /*<<< orphan*/ ) ; 
 struct virtio_gpu_framebuffer* to_virtio_gpu_framebuffer (scalar_t__) ; 
 int /*<<< orphan*/  virtio_gpu_cmd_resource_flush (struct virtio_gpu_device*,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  virtio_gpu_cmd_set_scanout (struct virtio_gpu_device*,int /*<<< orphan*/ ,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  virtio_gpu_cmd_transfer_to_host_2d (struct virtio_gpu_device*,struct virtio_gpu_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtio_gpu_primary_plane_update(struct drm_plane *plane,
					    struct drm_plane_state *old_state)
{
	struct drm_device *dev = plane->dev;
	struct virtio_gpu_device *vgdev = dev->dev_private;
	struct virtio_gpu_output *output = NULL;
	struct virtio_gpu_framebuffer *vgfb;
	struct virtio_gpu_object *bo;
	uint32_t handle;

	if (plane->state->crtc)
		output = drm_crtc_to_virtio_gpu_output(plane->state->crtc);
	if (old_state->crtc)
		output = drm_crtc_to_virtio_gpu_output(old_state->crtc);
	if (WARN_ON(!output))
		return;

	if (plane->state->fb && output->enabled) {
		vgfb = to_virtio_gpu_framebuffer(plane->state->fb);
		bo = gem_to_virtio_gpu_obj(vgfb->base.obj[0]);
		handle = bo->hw_res_handle;
		if (bo->dumb) {
			virtio_gpu_cmd_transfer_to_host_2d
				(vgdev, bo, 0,
				 cpu_to_le32(plane->state->src_w >> 16),
				 cpu_to_le32(plane->state->src_h >> 16),
				 cpu_to_le32(plane->state->src_x >> 16),
				 cpu_to_le32(plane->state->src_y >> 16), NULL);
		}
	} else {
		handle = 0;
	}

	DRM_DEBUG("handle 0x%x, crtc %dx%d+%d+%d, src %dx%d+%d+%d\n", handle,
		  plane->state->crtc_w, plane->state->crtc_h,
		  plane->state->crtc_x, plane->state->crtc_y,
		  plane->state->src_w >> 16,
		  plane->state->src_h >> 16,
		  plane->state->src_x >> 16,
		  plane->state->src_y >> 16);
	virtio_gpu_cmd_set_scanout(vgdev, output->index, handle,
				   plane->state->src_w >> 16,
				   plane->state->src_h >> 16,
				   plane->state->src_x >> 16,
				   plane->state->src_y >> 16);
	if (handle)
		virtio_gpu_cmd_resource_flush(vgdev, handle,
					      plane->state->src_x >> 16,
					      plane->state->src_y >> 16,
					      plane->state->src_w >> 16,
					      plane->state->src_h >> 16);
}