#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int x1; int y1; } ;
struct TYPE_5__ {unsigned int rotation; TYPE_3__ src; struct drm_framebuffer* fb; } ;
struct intel_plane_state {TYPE_2__* color_plane; TYPE_1__ base; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_6__ {int x; int y; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,int,int) ; 
 int EINVAL ; 
 int drm_rect_height (TYPE_3__*) ; 
 int drm_rect_width (TYPE_3__*) ; 
 int /*<<< orphan*/  intel_add_fb_offsets (int*,int*,struct intel_plane_state*,int) ; 
 int /*<<< orphan*/  intel_plane_compute_aligned_offset (int*,int*,struct intel_plane_state*,int) ; 
 int skl_max_plane_width (struct drm_framebuffer const*,int,unsigned int) ; 

__attribute__((used)) static int skl_check_nv12_aux_surface(struct intel_plane_state *plane_state)
{
	const struct drm_framebuffer *fb = plane_state->base.fb;
	unsigned int rotation = plane_state->base.rotation;
	int max_width = skl_max_plane_width(fb, 1, rotation);
	int max_height = 4096;
	int x = plane_state->base.src.x1 >> 17;
	int y = plane_state->base.src.y1 >> 17;
	int w = drm_rect_width(&plane_state->base.src) >> 17;
	int h = drm_rect_height(&plane_state->base.src) >> 17;
	u32 offset;

	intel_add_fb_offsets(&x, &y, plane_state, 1);
	offset = intel_plane_compute_aligned_offset(&x, &y, plane_state, 1);

	/* FIXME not quite sure how/if these apply to the chroma plane */
	if (w > max_width || h > max_height) {
		DRM_DEBUG_KMS("CbCr source size %dx%d too big (limit %dx%d)\n",
			      w, h, max_width, max_height);
		return -EINVAL;
	}

	plane_state->color_plane[1].offset = offset;
	plane_state->color_plane[1].x = x;
	plane_state->color_plane[1].y = y;

	return 0;
}