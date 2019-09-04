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
typedef  int uint64_t ;

/* Variables and functions */
#define  I915_FORMAT_MOD_X_TILED 130 
#define  I915_FORMAT_MOD_Y_TILED 129 
#define  I915_FORMAT_MOD_Y_TILED_CCS 128 
 unsigned int I915_TILING_NONE ; 
 unsigned int I915_TILING_X ; 
 unsigned int I915_TILING_Y ; 

__attribute__((used)) static unsigned int intel_fb_modifier_to_tiling(uint64_t fb_modifier)
{
	switch (fb_modifier) {
	case I915_FORMAT_MOD_X_TILED:
		return I915_TILING_X;
	case I915_FORMAT_MOD_Y_TILED:
	case I915_FORMAT_MOD_Y_TILED_CCS:
		return I915_TILING_Y;
	default:
		return I915_TILING_NONE;
	}
}