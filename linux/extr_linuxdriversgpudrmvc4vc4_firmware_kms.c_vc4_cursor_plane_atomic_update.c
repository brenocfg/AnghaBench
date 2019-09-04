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
typedef  scalar_t__ u32 ;
struct vc4_dev {int /*<<< orphan*/  firmware; } ;
struct vc4_crtc {scalar_t__* overscan; } ;
struct drm_plane_state {scalar_t__ crtc_x; scalar_t__ crtc_y; int crtc_w; scalar_t__ crtc_h; struct drm_framebuffer* fb; TYPE_3__* crtc; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct drm_plane {int /*<<< orphan*/  name; TYPE_2__ base; struct drm_plane_state* state; int /*<<< orphan*/  dev; } ;
struct drm_gem_cma_object {scalar_t__ paddr; } ;
struct drm_framebuffer {scalar_t__* offsets; int* pitches; } ;
typedef  int /*<<< orphan*/  packet_state ;
typedef  int /*<<< orphan*/  packet_info ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_6__ {TYPE_1__* state; } ;
struct TYPE_4__ {scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  RPI_FIRMWARE_SET_CURSOR_INFO ; 
 int /*<<< orphan*/  RPI_FIRMWARE_SET_CURSOR_STATE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 int rpi_firmware_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__**,int) ; 
 struct vc4_crtc* to_vc4_crtc (TYPE_3__*) ; 
 struct vc4_dev* to_vc4_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc4_cursor_plane_atomic_update(struct drm_plane *plane,
					   struct drm_plane_state *old_state)
{
	struct vc4_dev *vc4 = to_vc4_dev(plane->dev);
	struct drm_plane_state *state = plane->state;
	struct vc4_crtc *vc4_crtc = to_vc4_crtc(state->crtc);
	struct drm_framebuffer *fb = state->fb;
	struct drm_gem_cma_object *bo = drm_fb_cma_get_gem_obj(fb, 0);
	dma_addr_t addr = bo->paddr + fb->offsets[0];
	int ret;
	u32 packet_state[] = {
		state->crtc->state->active,
		state->crtc_x,
		state->crtc_y,
		0
	};
	WARN_ON_ONCE(fb->pitches[0] != state->crtc_w * 4);

	DRM_DEBUG_ATOMIC("[PLANE:%d:%s] update %dx%d cursor at %d,%d (0x%pad/%d)",
			 plane->base.id, plane->name,
			 state->crtc_w,
			 state->crtc_h,
			 state->crtc_x,
			 state->crtc_y,
			 &addr,
			 fb->pitches[0]);

	/* add on the top/left offsets when overscan is active */
	if (vc4_crtc) {
		packet_state[1] += vc4_crtc->overscan[0];
		packet_state[2] += vc4_crtc->overscan[1];
	}

	ret = rpi_firmware_property(vc4->firmware,
				    RPI_FIRMWARE_SET_CURSOR_STATE,
				    &packet_state,
				    sizeof(packet_state));
	if (ret || packet_state[0] != 0)
		DRM_ERROR("Failed to set cursor state: 0x%08x\n", packet_state[0]);

	/* Note: When the cursor contents change, the modesetting
	 * driver calls drm_mode_cursor_univeral() with
	 * DRM_MODE_CURSOR_BO, which means a new fb will be allocated.
	 */
	if (!old_state ||
	    state->crtc_w != old_state->crtc_w ||
	    state->crtc_h != old_state->crtc_h ||
	    fb != old_state->fb) {
		u32 packet_info[] = { state->crtc_w, state->crtc_h,
				      0, /* unused */
				      addr,
				      0, 0, /* hotx, hoty */};

		ret = rpi_firmware_property(vc4->firmware,
					    RPI_FIRMWARE_SET_CURSOR_INFO,
					    &packet_info,
					    sizeof(packet_info));
		if (ret || packet_info[0] != 0)
			DRM_ERROR("Failed to set cursor info: 0x%08x\n", packet_info[0]);
	}
}