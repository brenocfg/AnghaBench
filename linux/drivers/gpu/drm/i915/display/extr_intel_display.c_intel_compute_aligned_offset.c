#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {int /*<<< orphan*/  modifier; TYPE_1__* format; } ;
struct TYPE_2__ {unsigned int* cpp; } ;

/* Variables and functions */
 scalar_t__ drm_rotation_90_or_270 (unsigned int) ; 
 int /*<<< orphan*/  intel_adjust_tile_offset (int*,int*,unsigned int,unsigned int,unsigned int,unsigned int,int,int) ; 
 int /*<<< orphan*/  intel_tile_dims (struct drm_framebuffer const*,int,unsigned int*,unsigned int*) ; 
 unsigned int intel_tile_size (struct drm_i915_private*) ; 
 int /*<<< orphan*/  is_surface_linear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  swap (unsigned int,unsigned int) ; 

__attribute__((used)) static u32 intel_compute_aligned_offset(struct drm_i915_private *dev_priv,
					int *x, int *y,
					const struct drm_framebuffer *fb,
					int color_plane,
					unsigned int pitch,
					unsigned int rotation,
					u32 alignment)
{
	unsigned int cpp = fb->format->cpp[color_plane];
	u32 offset, offset_aligned;

	if (alignment)
		alignment--;

	if (!is_surface_linear(fb->modifier, color_plane)) {
		unsigned int tile_size, tile_width, tile_height;
		unsigned int tile_rows, tiles, pitch_tiles;

		tile_size = intel_tile_size(dev_priv);
		intel_tile_dims(fb, color_plane, &tile_width, &tile_height);

		if (drm_rotation_90_or_270(rotation)) {
			pitch_tiles = pitch / tile_height;
			swap(tile_width, tile_height);
		} else {
			pitch_tiles = pitch / (tile_width * cpp);
		}

		tile_rows = *y / tile_height;
		*y %= tile_height;

		tiles = *x / tile_width;
		*x %= tile_width;

		offset = (tile_rows * pitch_tiles + tiles) * tile_size;
		offset_aligned = offset & ~alignment;

		intel_adjust_tile_offset(x, y, tile_width, tile_height,
					 tile_size, pitch_tiles,
					 offset, offset_aligned);
	} else {
		offset = *y * pitch + *x * cpp;
		offset_aligned = offset & ~alignment;

		*y = (offset & alignment) / pitch;
		*x = ((offset & alignment) - *y * pitch) / cpp;
	}

	return offset_aligned;
}