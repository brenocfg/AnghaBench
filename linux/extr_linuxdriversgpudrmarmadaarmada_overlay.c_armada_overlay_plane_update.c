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
typedef  void* uint32_t ;
struct drm_plane_state {int crtc_x; int crtc_y; unsigned int crtc_h; unsigned int crtc_w; void* src_w; void* src_h; void* src_y; void* src_x; } ;
struct drm_plane {int /*<<< orphan*/  dev; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct drm_atomic_state {struct drm_modeset_acquire_ctx* acquire_ctx; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct drm_plane_state*) ; 
 int PTR_ERR (struct drm_plane_state*) ; 
 struct drm_plane_state* drm_atomic_get_plane_state (struct drm_atomic_state*,struct drm_plane*) ; 
 int drm_atomic_nonblocking_commit (struct drm_atomic_state*) ; 
 int drm_atomic_set_crtc_for_plane (struct drm_plane_state*,struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_atomic_set_fb_for_plane (struct drm_plane_state*,struct drm_framebuffer*) ; 
 struct drm_atomic_state* drm_atomic_state_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  trace_armada_ovl_plane_update (struct drm_plane*,struct drm_crtc*,struct drm_framebuffer*,int,int,unsigned int,unsigned int,void*,void*,void*,void*) ; 

__attribute__((used)) static int
armada_overlay_plane_update(struct drm_plane *plane, struct drm_crtc *crtc,
	struct drm_framebuffer *fb,
	int crtc_x, int crtc_y, unsigned crtc_w, unsigned crtc_h,
	uint32_t src_x, uint32_t src_y, uint32_t src_w, uint32_t src_h,
	struct drm_modeset_acquire_ctx *ctx)
{
	struct drm_atomic_state *state;
	struct drm_plane_state *plane_state;
	int ret = 0;

	trace_armada_ovl_plane_update(plane, crtc, fb,
				 crtc_x, crtc_y, crtc_w, crtc_h,
				 src_x, src_y, src_w, src_h);

	state = drm_atomic_state_alloc(plane->dev);
	if (!state)
		return -ENOMEM;

	state->acquire_ctx = ctx;
	plane_state = drm_atomic_get_plane_state(state, plane);
	if (IS_ERR(plane_state)) {
		ret = PTR_ERR(plane_state);
		goto fail;
	}

	ret = drm_atomic_set_crtc_for_plane(plane_state, crtc);
	if (ret != 0)
		goto fail;

	drm_atomic_set_fb_for_plane(plane_state, fb);
	plane_state->crtc_x = crtc_x;
	plane_state->crtc_y = crtc_y;
	plane_state->crtc_h = crtc_h;
	plane_state->crtc_w = crtc_w;
	plane_state->src_x = src_x;
	plane_state->src_y = src_y;
	plane_state->src_h = src_h;
	plane_state->src_w = src_w;

	ret = drm_atomic_nonblocking_commit(state);
fail:
	drm_atomic_state_put(state);
	return ret;
}