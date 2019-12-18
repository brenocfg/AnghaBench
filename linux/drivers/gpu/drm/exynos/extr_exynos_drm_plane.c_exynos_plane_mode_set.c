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
struct TYPE_6__ {int x; int y; unsigned int w; unsigned int h; } ;
struct TYPE_4__ {unsigned int x; unsigned int y; unsigned int w; unsigned int h; } ;
struct drm_plane_state {int crtc_x; int crtc_y; unsigned int crtc_w; unsigned int crtc_h; int src_x; int src_y; int src_w; int src_h; int /*<<< orphan*/  state; struct drm_crtc* crtc; } ;
struct exynos_drm_plane_state {unsigned int h_ratio; unsigned int v_ratio; TYPE_3__ crtc; TYPE_1__ src; struct drm_plane_state base; } ;
struct drm_display_mode {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct drm_crtc_state {struct drm_display_mode adjusted_mode; } ;
struct drm_crtc {TYPE_2__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int,int,unsigned int,unsigned int) ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (int /*<<< orphan*/ ,struct drm_crtc*) ; 
 unsigned int exynos_plane_get_size (int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_plane_mode_set(struct exynos_drm_plane_state *exynos_state)
{
	struct drm_plane_state *state = &exynos_state->base;
	struct drm_crtc *crtc = state->crtc;
	struct drm_crtc_state *crtc_state =
			drm_atomic_get_existing_crtc_state(state->state, crtc);
	struct drm_display_mode *mode = &crtc_state->adjusted_mode;
	int crtc_x, crtc_y;
	unsigned int crtc_w, crtc_h;
	unsigned int src_x, src_y;
	unsigned int src_w, src_h;
	unsigned int actual_w;
	unsigned int actual_h;

	/*
	 * The original src/dest coordinates are stored in exynos_state->base,
	 * but we want to keep another copy internal to our driver that we can
	 * clip/modify ourselves.
	 */

	crtc_x = state->crtc_x;
	crtc_y = state->crtc_y;
	crtc_w = state->crtc_w;
	crtc_h = state->crtc_h;

	src_x = state->src_x >> 16;
	src_y = state->src_y >> 16;
	src_w = state->src_w >> 16;
	src_h = state->src_h >> 16;

	/* set ratio */
	exynos_state->h_ratio = (src_w << 16) / crtc_w;
	exynos_state->v_ratio = (src_h << 16) / crtc_h;

	/* clip to visible area */
	actual_w = exynos_plane_get_size(crtc_x, crtc_w, mode->hdisplay);
	actual_h = exynos_plane_get_size(crtc_y, crtc_h, mode->vdisplay);

	if (crtc_x < 0) {
		if (actual_w)
			src_x += ((-crtc_x) * exynos_state->h_ratio) >> 16;
		crtc_x = 0;
	}

	if (crtc_y < 0) {
		if (actual_h)
			src_y += ((-crtc_y) * exynos_state->v_ratio) >> 16;
		crtc_y = 0;
	}

	/* set drm framebuffer data. */
	exynos_state->src.x = src_x;
	exynos_state->src.y = src_y;
	exynos_state->src.w = (actual_w * exynos_state->h_ratio) >> 16;
	exynos_state->src.h = (actual_h * exynos_state->v_ratio) >> 16;

	/* set plane range to be displayed. */
	exynos_state->crtc.x = crtc_x;
	exynos_state->crtc.y = crtc_y;
	exynos_state->crtc.w = actual_w;
	exynos_state->crtc.h = actual_h;

	DRM_DEV_DEBUG_KMS(crtc->dev->dev,
			  "plane : offset_x/y(%d,%d), width/height(%d,%d)",
			  exynos_state->crtc.x, exynos_state->crtc.y,
			  exynos_state->crtc.w, exynos_state->crtc.h);
}