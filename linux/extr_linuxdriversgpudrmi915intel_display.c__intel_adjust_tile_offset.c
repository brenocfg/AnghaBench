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
typedef  scalar_t__ u32 ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {scalar_t__ modifier; TYPE_1__* format; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned int* cpp; } ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_MOD_LINEAR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __intel_adjust_tile_offset (int*,int*,unsigned int,unsigned int,unsigned int,unsigned int,scalar_t__,scalar_t__) ; 
 scalar_t__ drm_rotation_90_or_270 (unsigned int) ; 
 unsigned int intel_fb_pitch (struct drm_framebuffer const*,int,unsigned int) ; 
 int /*<<< orphan*/  intel_tile_dims (struct drm_framebuffer const*,int,unsigned int*,unsigned int*) ; 
 unsigned int intel_tile_size (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  swap (unsigned int,unsigned int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 _intel_adjust_tile_offset(int *x, int *y,
				     const struct drm_framebuffer *fb, int plane,
				     unsigned int rotation,
				     u32 old_offset, u32 new_offset)
{
	const struct drm_i915_private *dev_priv = to_i915(fb->dev);
	unsigned int cpp = fb->format->cpp[plane];
	unsigned int pitch = intel_fb_pitch(fb, plane, rotation);

	WARN_ON(new_offset > old_offset);

	if (fb->modifier != DRM_FORMAT_MOD_LINEAR) {
		unsigned int tile_size, tile_width, tile_height;
		unsigned int pitch_tiles;

		tile_size = intel_tile_size(dev_priv);
		intel_tile_dims(fb, plane, &tile_width, &tile_height);

		if (drm_rotation_90_or_270(rotation)) {
			pitch_tiles = pitch / tile_height;
			swap(tile_width, tile_height);
		} else {
			pitch_tiles = pitch / (tile_width * cpp);
		}

		__intel_adjust_tile_offset(x, y, tile_width, tile_height,
					   tile_size, pitch_tiles,
					   old_offset, new_offset);
	} else {
		old_offset += *y * pitch + *x * cpp;

		*y = (old_offset - new_offset) / pitch;
		*x = ((old_offset - new_offset) - *y * pitch) / cpp;
	}

	return new_offset;
}