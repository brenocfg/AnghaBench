#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct intel_rotation_info {TYPE_5__* plane; } ;
struct drm_rect {int x1; int y1; unsigned int x2; unsigned int y2; } ;
struct TYPE_9__ {unsigned int rotation; struct drm_rect src; struct drm_framebuffer* fb; TYPE_1__* plane; } ;
struct TYPE_14__ {int /*<<< orphan*/  type; struct intel_rotation_info rotated; } ;
struct intel_plane_state {TYPE_6__* color_plane; TYPE_2__ base; TYPE_7__ view; } ;
struct intel_framebuffer {TYPE_4__* normal; } ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {unsigned int* pitches; TYPE_3__* format; int /*<<< orphan*/  modifier; } ;
struct TYPE_13__ {unsigned int stride; unsigned int x; unsigned int y; scalar_t__ offset; } ;
struct TYPE_12__ {unsigned int offset; unsigned int width; unsigned int height; void* stride; } ;
struct TYPE_11__ {unsigned int x; unsigned int y; } ;
struct TYPE_10__ {int num_planes; int hsub; int vsub; unsigned int* cpp; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 
 int /*<<< orphan*/  DRM_MODE_ROTATE_270 ; 
 int /*<<< orphan*/  I915_GGTT_VIEW_REMAPPED ; 
 int /*<<< orphan*/  I915_GGTT_VIEW_ROTATED ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int drm_rect_height (struct drm_rect*) ; 
 int /*<<< orphan*/  drm_rect_rotate (struct drm_rect*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_rect_translate (struct drm_rect*,unsigned int,unsigned int) ; 
 int drm_rect_width (struct drm_rect*) ; 
 scalar_t__ drm_rotation_90_or_270 (unsigned int) ; 
 int /*<<< orphan*/  intel_adjust_tile_offset (unsigned int*,unsigned int*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int intel_compute_aligned_offset (struct drm_i915_private*,unsigned int*,unsigned int*,struct drm_framebuffer*,int,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  intel_tile_dims (struct drm_framebuffer*,int,unsigned int*,unsigned int*) ; 
 unsigned int intel_tile_size (struct drm_i915_private*) ; 
 int /*<<< orphan*/  is_ccs_modifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  swap (unsigned int,unsigned int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_framebuffer* to_intel_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static void
intel_plane_remap_gtt(struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv =
		to_i915(plane_state->base.plane->dev);
	struct drm_framebuffer *fb = plane_state->base.fb;
	struct intel_framebuffer *intel_fb = to_intel_framebuffer(fb);
	struct intel_rotation_info *info = &plane_state->view.rotated;
	unsigned int rotation = plane_state->base.rotation;
	int i, num_planes = fb->format->num_planes;
	unsigned int tile_size = intel_tile_size(dev_priv);
	unsigned int src_x, src_y;
	unsigned int src_w, src_h;
	u32 gtt_offset = 0;

	memset(&plane_state->view, 0, sizeof(plane_state->view));
	plane_state->view.type = drm_rotation_90_or_270(rotation) ?
		I915_GGTT_VIEW_ROTATED : I915_GGTT_VIEW_REMAPPED;

	src_x = plane_state->base.src.x1 >> 16;
	src_y = plane_state->base.src.y1 >> 16;
	src_w = drm_rect_width(&plane_state->base.src) >> 16;
	src_h = drm_rect_height(&plane_state->base.src) >> 16;

	WARN_ON(is_ccs_modifier(fb->modifier));

	/* Make src coordinates relative to the viewport */
	drm_rect_translate(&plane_state->base.src,
			   -(src_x << 16), -(src_y << 16));

	/* Rotate src coordinates to match rotated GTT view */
	if (drm_rotation_90_or_270(rotation))
		drm_rect_rotate(&plane_state->base.src,
				src_w << 16, src_h << 16,
				DRM_MODE_ROTATE_270);

	for (i = 0; i < num_planes; i++) {
		unsigned int hsub = i ? fb->format->hsub : 1;
		unsigned int vsub = i ? fb->format->vsub : 1;
		unsigned int cpp = fb->format->cpp[i];
		unsigned int tile_width, tile_height;
		unsigned int width, height;
		unsigned int pitch_tiles;
		unsigned int x, y;
		u32 offset;

		intel_tile_dims(fb, i, &tile_width, &tile_height);

		x = src_x / hsub;
		y = src_y / vsub;
		width = src_w / hsub;
		height = src_h / vsub;

		/*
		 * First pixel of the src viewport from the
		 * start of the normal gtt mapping.
		 */
		x += intel_fb->normal[i].x;
		y += intel_fb->normal[i].y;

		offset = intel_compute_aligned_offset(dev_priv, &x, &y,
						      fb, i, fb->pitches[i],
						      DRM_MODE_ROTATE_0, tile_size);
		offset /= tile_size;

		info->plane[i].offset = offset;
		info->plane[i].stride = DIV_ROUND_UP(fb->pitches[i],
						     tile_width * cpp);
		info->plane[i].width = DIV_ROUND_UP(x + width, tile_width);
		info->plane[i].height = DIV_ROUND_UP(y + height, tile_height);

		if (drm_rotation_90_or_270(rotation)) {
			struct drm_rect r;

			/* rotate the x/y offsets to match the GTT view */
			r.x1 = x;
			r.y1 = y;
			r.x2 = x + width;
			r.y2 = y + height;
			drm_rect_rotate(&r,
					info->plane[i].width * tile_width,
					info->plane[i].height * tile_height,
					DRM_MODE_ROTATE_270);
			x = r.x1;
			y = r.y1;

			pitch_tiles = info->plane[i].height;
			plane_state->color_plane[i].stride = pitch_tiles * tile_height;

			/* rotate the tile dimensions to match the GTT view */
			swap(tile_width, tile_height);
		} else {
			pitch_tiles = info->plane[i].width;
			plane_state->color_plane[i].stride = pitch_tiles * tile_width * cpp;
		}

		/*
		 * We only keep the x/y offsets, so push all of the
		 * gtt offset into the x/y offsets.
		 */
		intel_adjust_tile_offset(&x, &y,
					 tile_width, tile_height,
					 tile_size, pitch_tiles,
					 gtt_offset * tile_size, 0);

		gtt_offset += info->plane[i].width * info->plane[i].height;

		plane_state->color_plane[i].offset = 0;
		plane_state->color_plane[i].x = x;
		plane_state->color_plane[i].y = y;
	}
}