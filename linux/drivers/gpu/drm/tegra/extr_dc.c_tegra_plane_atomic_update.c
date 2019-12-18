#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  window ;
struct tegra_plane_state {int /*<<< orphan*/  swap; int /*<<< orphan*/  format; int /*<<< orphan*/  tiling; scalar_t__ bottom_up; } ;
struct tegra_plane {int dummy; } ;
struct TYPE_8__ {int x; int y; int w; int h; } ;
struct TYPE_7__ {int x; int y; int w; int h; } ;
struct tegra_dc_window {int bits_per_pixel; int bottom_up; int /*<<< orphan*/ * stride; scalar_t__* base; int /*<<< orphan*/  swap; int /*<<< orphan*/  format; int /*<<< orphan*/  tiling; int /*<<< orphan*/  zpos; TYPE_2__ dst; TYPE_1__ src; } ;
struct tegra_bo {scalar_t__ paddr; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {TYPE_4__* state; } ;
struct drm_framebuffer {int /*<<< orphan*/ * pitches; scalar_t__* offsets; TYPE_3__* format; } ;
struct TYPE_11__ {int x1; int y1; } ;
struct TYPE_10__ {int /*<<< orphan*/  normalized_zpos; TYPE_5__ dst; TYPE_5__ src; int /*<<< orphan*/  visible; struct drm_framebuffer* fb; int /*<<< orphan*/  crtc; } ;
struct TYPE_9__ {int* cpp; unsigned int num_planes; } ;

/* Variables and functions */
 int drm_rect_height (TYPE_5__*) ; 
 int drm_rect_width (TYPE_5__*) ; 
 int /*<<< orphan*/  memset (struct tegra_dc_window*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tegra_dc_setup_window (struct tegra_plane*,struct tegra_dc_window*) ; 
 struct tegra_bo* tegra_fb_get_plane (struct drm_framebuffer*,unsigned int) ; 
 scalar_t__ tegra_fb_is_bottom_up (struct drm_framebuffer*) ; 
 void tegra_plane_atomic_disable (struct drm_plane*,struct drm_plane_state*) ; 
 struct tegra_plane* to_tegra_plane (struct drm_plane*) ; 
 struct tegra_plane_state* to_tegra_plane_state (TYPE_4__*) ; 

__attribute__((used)) static void tegra_plane_atomic_update(struct drm_plane *plane,
				      struct drm_plane_state *old_state)
{
	struct tegra_plane_state *state = to_tegra_plane_state(plane->state);
	struct drm_framebuffer *fb = plane->state->fb;
	struct tegra_plane *p = to_tegra_plane(plane);
	struct tegra_dc_window window;
	unsigned int i;

	/* rien ne va plus */
	if (!plane->state->crtc || !plane->state->fb)
		return;

	if (!plane->state->visible)
		return tegra_plane_atomic_disable(plane, old_state);

	memset(&window, 0, sizeof(window));
	window.src.x = plane->state->src.x1 >> 16;
	window.src.y = plane->state->src.y1 >> 16;
	window.src.w = drm_rect_width(&plane->state->src) >> 16;
	window.src.h = drm_rect_height(&plane->state->src) >> 16;
	window.dst.x = plane->state->dst.x1;
	window.dst.y = plane->state->dst.y1;
	window.dst.w = drm_rect_width(&plane->state->dst);
	window.dst.h = drm_rect_height(&plane->state->dst);
	window.bits_per_pixel = fb->format->cpp[0] * 8;
	window.bottom_up = tegra_fb_is_bottom_up(fb) || state->bottom_up;

	/* copy from state */
	window.zpos = plane->state->normalized_zpos;
	window.tiling = state->tiling;
	window.format = state->format;
	window.swap = state->swap;

	for (i = 0; i < fb->format->num_planes; i++) {
		struct tegra_bo *bo = tegra_fb_get_plane(fb, i);

		window.base[i] = bo->paddr + fb->offsets[i];

		/*
		 * Tegra uses a shared stride for UV planes. Framebuffers are
		 * already checked for this in the tegra_plane_atomic_check()
		 * function, so it's safe to ignore the V-plane pitch here.
		 */
		if (i < 2)
			window.stride[i] = fb->pitches[i];
	}

	tegra_dc_setup_window(p, &window);
}