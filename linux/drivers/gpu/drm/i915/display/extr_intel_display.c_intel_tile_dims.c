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
struct drm_framebuffer {int /*<<< orphan*/  dev; TYPE_1__* format; } ;
struct TYPE_2__ {unsigned int* cpp; } ;

/* Variables and functions */
 unsigned int intel_tile_size (int /*<<< orphan*/ ) ; 
 unsigned int intel_tile_width_bytes (struct drm_framebuffer const*,int) ; 
 int /*<<< orphan*/  to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_tile_dims(const struct drm_framebuffer *fb, int color_plane,
			    unsigned int *tile_width,
			    unsigned int *tile_height)
{
	unsigned int tile_width_bytes = intel_tile_width_bytes(fb, color_plane);
	unsigned int cpp = fb->format->cpp[color_plane];

	*tile_width = tile_width_bytes / cpp;
	*tile_height = intel_tile_size(to_i915(fb->dev)) / tile_width_bytes;
}