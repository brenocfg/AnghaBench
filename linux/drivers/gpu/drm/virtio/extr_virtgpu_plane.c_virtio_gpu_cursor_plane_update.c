#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_14__ {void* y; void* x; } ;
struct TYPE_13__ {void* type; } ;
struct TYPE_15__ {TYPE_5__ pos; TYPE_4__ hdr; void* hot_y; void* hot_x; void* resource_id; } ;
struct virtio_gpu_output {TYPE_6__ cursor; } ;
struct TYPE_11__ {int /*<<< orphan*/  resv; } ;
struct TYPE_12__ {TYPE_2__ base; } ;
struct virtio_gpu_object {TYPE_3__ tbo; scalar_t__ dumb; scalar_t__ hw_res_handle; } ;
struct TYPE_10__ {int /*<<< orphan*/ * obj; } ;
struct virtio_gpu_framebuffer {TYPE_8__* fence; TYPE_1__ base; } ;
struct virtio_gpu_device {int dummy; } ;
struct drm_plane_state {TYPE_9__* fb; scalar_t__ crtc; } ;
struct drm_plane {TYPE_7__* state; struct drm_device* dev; } ;
struct drm_device {struct virtio_gpu_device* dev_private; } ;
struct TYPE_18__ {scalar_t__ hot_y; scalar_t__ hot_x; } ;
struct TYPE_17__ {int /*<<< orphan*/  f; } ;
struct TYPE_16__ {scalar_t__ crtc_y; scalar_t__ crtc_x; TYPE_9__* fb; scalar_t__ crtc_h; scalar_t__ crtc_w; scalar_t__ crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__,scalar_t__,...) ; 
 scalar_t__ VIRTIO_GPU_CMD_MOVE_CURSOR ; 
 scalar_t__ VIRTIO_GPU_CMD_UPDATE_CURSOR ; 
 scalar_t__ WARN_ON (int) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_resv_add_excl_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct virtio_gpu_output* drm_crtc_to_virtio_gpu_output (scalar_t__) ; 
 struct virtio_gpu_object* gem_to_virtio_gpu_obj (int /*<<< orphan*/ ) ; 
 struct virtio_gpu_framebuffer* to_virtio_gpu_framebuffer (TYPE_9__*) ; 
 int /*<<< orphan*/  virtio_gpu_cmd_transfer_to_host_2d (struct virtio_gpu_device*,struct virtio_gpu_object*,int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  virtio_gpu_cursor_ping (struct virtio_gpu_device*,struct virtio_gpu_output*) ; 
 int virtio_gpu_object_reserve (struct virtio_gpu_object*,int) ; 
 int /*<<< orphan*/  virtio_gpu_object_unreserve (struct virtio_gpu_object*) ; 
 int /*<<< orphan*/  virtio_gpu_object_wait (struct virtio_gpu_object*,int) ; 

__attribute__((used)) static void virtio_gpu_cursor_plane_update(struct drm_plane *plane,
					   struct drm_plane_state *old_state)
{
	struct drm_device *dev = plane->dev;
	struct virtio_gpu_device *vgdev = dev->dev_private;
	struct virtio_gpu_output *output = NULL;
	struct virtio_gpu_framebuffer *vgfb;
	struct virtio_gpu_object *bo = NULL;
	uint32_t handle;
	int ret = 0;

	if (plane->state->crtc)
		output = drm_crtc_to_virtio_gpu_output(plane->state->crtc);
	if (old_state->crtc)
		output = drm_crtc_to_virtio_gpu_output(old_state->crtc);
	if (WARN_ON(!output))
		return;

	if (plane->state->fb) {
		vgfb = to_virtio_gpu_framebuffer(plane->state->fb);
		bo = gem_to_virtio_gpu_obj(vgfb->base.obj[0]);
		handle = bo->hw_res_handle;
	} else {
		handle = 0;
	}

	if (bo && bo->dumb && (plane->state->fb != old_state->fb)) {
		/* new cursor -- update & wait */
		virtio_gpu_cmd_transfer_to_host_2d
			(vgdev, bo, 0,
			 cpu_to_le32(plane->state->crtc_w),
			 cpu_to_le32(plane->state->crtc_h),
			 0, 0, vgfb->fence);
		ret = virtio_gpu_object_reserve(bo, false);
		if (!ret) {
			dma_resv_add_excl_fence(bo->tbo.base.resv,
							  &vgfb->fence->f);
			dma_fence_put(&vgfb->fence->f);
			vgfb->fence = NULL;
			virtio_gpu_object_unreserve(bo);
			virtio_gpu_object_wait(bo, false);
		}
	}

	if (plane->state->fb != old_state->fb) {
		DRM_DEBUG("update, handle %d, pos +%d+%d, hot %d,%d\n", handle,
			  plane->state->crtc_x,
			  plane->state->crtc_y,
			  plane->state->fb ? plane->state->fb->hot_x : 0,
			  plane->state->fb ? plane->state->fb->hot_y : 0);
		output->cursor.hdr.type =
			cpu_to_le32(VIRTIO_GPU_CMD_UPDATE_CURSOR);
		output->cursor.resource_id = cpu_to_le32(handle);
		if (plane->state->fb) {
			output->cursor.hot_x =
				cpu_to_le32(plane->state->fb->hot_x);
			output->cursor.hot_y =
				cpu_to_le32(plane->state->fb->hot_y);
		} else {
			output->cursor.hot_x = cpu_to_le32(0);
			output->cursor.hot_y = cpu_to_le32(0);
		}
	} else {
		DRM_DEBUG("move +%d+%d\n",
			  plane->state->crtc_x,
			  plane->state->crtc_y);
		output->cursor.hdr.type =
			cpu_to_le32(VIRTIO_GPU_CMD_MOVE_CURSOR);
	}
	output->cursor.pos.x = cpu_to_le32(plane->state->crtc_x);
	output->cursor.pos.y = cpu_to_le32(plane->state->crtc_y);
	virtio_gpu_cursor_ping(vgdev, output);
}