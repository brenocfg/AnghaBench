#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {unsigned int rotation; int /*<<< orphan*/  src; int /*<<< orphan*/  fb; } ;
struct intel_plane_state {TYPE_5__ base; TYPE_3__* color_plane; int /*<<< orphan*/  view; } ;
struct TYPE_13__ {int width; int height; TYPE_1__* format; } ;
struct intel_framebuffer {TYPE_6__ base; TYPE_4__* normal; TYPE_2__* rotated; } ;
struct TYPE_11__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; scalar_t__ offset; int /*<<< orphan*/  stride; } ;
struct TYPE_9__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {int num_planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ROTATE_270 ; 
 int /*<<< orphan*/  drm_rect_rotate (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_rotation_90_or_270 (unsigned int) ; 
 int /*<<< orphan*/  intel_fb_pitch (TYPE_6__*,int,unsigned int) ; 
 int /*<<< orphan*/  intel_fill_fb_ggtt_view (int /*<<< orphan*/ *,TYPE_6__*,unsigned int) ; 
 int intel_plane_check_stride (struct intel_plane_state*) ; 
 scalar_t__ intel_plane_needs_remap (struct intel_plane_state*) ; 
 int /*<<< orphan*/  intel_plane_remap_gtt (struct intel_plane_state*) ; 
 struct intel_framebuffer* to_intel_framebuffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_plane_compute_gtt(struct intel_plane_state *plane_state)
{
	const struct intel_framebuffer *fb =
		to_intel_framebuffer(plane_state->base.fb);
	unsigned int rotation = plane_state->base.rotation;
	int i, num_planes;

	if (!fb)
		return 0;

	num_planes = fb->base.format->num_planes;

	if (intel_plane_needs_remap(plane_state)) {
		intel_plane_remap_gtt(plane_state);

		/*
		 * Sometimes even remapping can't overcome
		 * the stride limitations :( Can happen with
		 * big plane sizes and suitably misaligned
		 * offsets.
		 */
		return intel_plane_check_stride(plane_state);
	}

	intel_fill_fb_ggtt_view(&plane_state->view, &fb->base, rotation);

	for (i = 0; i < num_planes; i++) {
		plane_state->color_plane[i].stride = intel_fb_pitch(&fb->base, i, rotation);
		plane_state->color_plane[i].offset = 0;

		if (drm_rotation_90_or_270(rotation)) {
			plane_state->color_plane[i].x = fb->rotated[i].x;
			plane_state->color_plane[i].y = fb->rotated[i].y;
		} else {
			plane_state->color_plane[i].x = fb->normal[i].x;
			plane_state->color_plane[i].y = fb->normal[i].y;
		}
	}

	/* Rotate src coordinates to match rotated GTT view */
	if (drm_rotation_90_or_270(rotation))
		drm_rect_rotate(&plane_state->base.src,
				fb->base.width << 16, fb->base.height << 16,
				DRM_MODE_ROTATE_270);

	return intel_plane_check_stride(plane_state);
}