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
typedef  int uint32_t ;
struct TYPE_2__ {int bit_6_swizzle_x; int bit_6_swizzle_y; } ;
struct drm_i915_private {TYPE_1__ mm; int /*<<< orphan*/  quirks; scalar_t__ preserve_bios_swizzle; } ;

/* Variables and functions */
 int /*<<< orphan*/  C0DRB3 ; 
 int /*<<< orphan*/  C1DRB3 ; 
 int /*<<< orphan*/  DCC ; 
 int /*<<< orphan*/  DCC2 ; 
 int DCC2_MODIFIED_ENHANCED_DISABLE ; 
#define  DCC_ADDRESSING_MODE_DUAL_CHANNEL_ASYMMETRIC 130 
#define  DCC_ADDRESSING_MODE_DUAL_CHANNEL_INTERLEAVED 129 
 int DCC_ADDRESSING_MODE_MASK ; 
#define  DCC_ADDRESSING_MODE_SINGLE_CHANNEL 128 
 int DCC_CHANNEL_XOR_BIT_17 ; 
 int DCC_CHANNEL_XOR_DISABLE ; 
 int /*<<< orphan*/  DISP_ARB_CTL ; 
 int DISP_TILE_SURFACE_SWIZZLING ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int I915_BIT_6_SWIZZLE_9 ; 
 int I915_BIT_6_SWIZZLE_9_10 ; 
 int I915_BIT_6_SWIZZLE_9_10_11 ; 
 int I915_BIT_6_SWIZZLE_9_10_17 ; 
 int I915_BIT_6_SWIZZLE_9_11 ; 
 int I915_BIT_6_SWIZZLE_9_17 ; 
 int I915_BIT_6_SWIZZLE_NONE ; 
 int I915_BIT_6_SWIZZLE_UNKNOWN ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ I915_READ16 (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN2 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN4 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN5 (struct drm_i915_private*) ; 
 scalar_t__ IS_I915G (struct drm_i915_private*) ; 
 scalar_t__ IS_I945G (struct drm_i915_private*) ; 
 scalar_t__ IS_MOBILE (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int MAD_DIMM_A_SIZE_MASK ; 
 int MAD_DIMM_B_SIZE_MASK ; 
 int /*<<< orphan*/  MAD_DIMM_C0 ; 
 int /*<<< orphan*/  MAD_DIMM_C1 ; 
 int /*<<< orphan*/  QUIRK_PIN_SWIZZLED_PAGES ; 

void
i915_gem_detect_bit_6_swizzle(struct drm_i915_private *dev_priv)
{
	uint32_t swizzle_x = I915_BIT_6_SWIZZLE_UNKNOWN;
	uint32_t swizzle_y = I915_BIT_6_SWIZZLE_UNKNOWN;

	if (INTEL_GEN(dev_priv) >= 8 || IS_VALLEYVIEW(dev_priv)) {
		/*
		 * On BDW+, swizzling is not used. We leave the CPU memory
		 * controller in charge of optimizing memory accesses without
		 * the extra address manipulation GPU side.
		 *
		 * VLV and CHV don't have GPU swizzling.
		 */
		swizzle_x = I915_BIT_6_SWIZZLE_NONE;
		swizzle_y = I915_BIT_6_SWIZZLE_NONE;
	} else if (INTEL_GEN(dev_priv) >= 6) {
		if (dev_priv->preserve_bios_swizzle) {
			if (I915_READ(DISP_ARB_CTL) &
			    DISP_TILE_SURFACE_SWIZZLING) {
				swizzle_x = I915_BIT_6_SWIZZLE_9_10;
				swizzle_y = I915_BIT_6_SWIZZLE_9;
			} else {
				swizzle_x = I915_BIT_6_SWIZZLE_NONE;
				swizzle_y = I915_BIT_6_SWIZZLE_NONE;
			}
		} else {
			uint32_t dimm_c0, dimm_c1;
			dimm_c0 = I915_READ(MAD_DIMM_C0);
			dimm_c1 = I915_READ(MAD_DIMM_C1);
			dimm_c0 &= MAD_DIMM_A_SIZE_MASK | MAD_DIMM_B_SIZE_MASK;
			dimm_c1 &= MAD_DIMM_A_SIZE_MASK | MAD_DIMM_B_SIZE_MASK;
			/* Enable swizzling when the channels are populated
			 * with identically sized dimms. We don't need to check
			 * the 3rd channel because no cpu with gpu attached
			 * ships in that configuration. Also, swizzling only
			 * makes sense for 2 channels anyway. */
			if (dimm_c0 == dimm_c1) {
				swizzle_x = I915_BIT_6_SWIZZLE_9_10;
				swizzle_y = I915_BIT_6_SWIZZLE_9;
			} else {
				swizzle_x = I915_BIT_6_SWIZZLE_NONE;
				swizzle_y = I915_BIT_6_SWIZZLE_NONE;
			}
		}
	} else if (IS_GEN5(dev_priv)) {
		/* On Ironlake whatever DRAM config, GPU always do
		 * same swizzling setup.
		 */
		swizzle_x = I915_BIT_6_SWIZZLE_9_10;
		swizzle_y = I915_BIT_6_SWIZZLE_9;
	} else if (IS_GEN2(dev_priv)) {
		/* As far as we know, the 865 doesn't have these bit 6
		 * swizzling issues.
		 */
		swizzle_x = I915_BIT_6_SWIZZLE_NONE;
		swizzle_y = I915_BIT_6_SWIZZLE_NONE;
	} else if (IS_MOBILE(dev_priv) ||
		   IS_I915G(dev_priv) || IS_I945G(dev_priv)) {
		uint32_t dcc;

		/* On 9xx chipsets, channel interleave by the CPU is
		 * determined by DCC.  For single-channel, neither the CPU
		 * nor the GPU do swizzling.  For dual channel interleaved,
		 * the GPU's interleave is bit 9 and 10 for X tiled, and bit
		 * 9 for Y tiled.  The CPU's interleave is independent, and
		 * can be based on either bit 11 (haven't seen this yet) or
		 * bit 17 (common).
		 */
		dcc = I915_READ(DCC);
		switch (dcc & DCC_ADDRESSING_MODE_MASK) {
		case DCC_ADDRESSING_MODE_SINGLE_CHANNEL:
		case DCC_ADDRESSING_MODE_DUAL_CHANNEL_ASYMMETRIC:
			swizzle_x = I915_BIT_6_SWIZZLE_NONE;
			swizzle_y = I915_BIT_6_SWIZZLE_NONE;
			break;
		case DCC_ADDRESSING_MODE_DUAL_CHANNEL_INTERLEAVED:
			if (dcc & DCC_CHANNEL_XOR_DISABLE) {
				/* This is the base swizzling by the GPU for
				 * tiled buffers.
				 */
				swizzle_x = I915_BIT_6_SWIZZLE_9_10;
				swizzle_y = I915_BIT_6_SWIZZLE_9;
			} else if ((dcc & DCC_CHANNEL_XOR_BIT_17) == 0) {
				/* Bit 11 swizzling by the CPU in addition. */
				swizzle_x = I915_BIT_6_SWIZZLE_9_10_11;
				swizzle_y = I915_BIT_6_SWIZZLE_9_11;
			} else {
				/* Bit 17 swizzling by the CPU in addition. */
				swizzle_x = I915_BIT_6_SWIZZLE_9_10_17;
				swizzle_y = I915_BIT_6_SWIZZLE_9_17;
			}
			break;
		}

		/* check for L-shaped memory aka modified enhanced addressing */
		if (IS_GEN4(dev_priv) &&
		    !(I915_READ(DCC2) & DCC2_MODIFIED_ENHANCED_DISABLE)) {
			swizzle_x = I915_BIT_6_SWIZZLE_UNKNOWN;
			swizzle_y = I915_BIT_6_SWIZZLE_UNKNOWN;
		}

		if (dcc == 0xffffffff) {
			DRM_ERROR("Couldn't read from MCHBAR.  "
				  "Disabling tiling.\n");
			swizzle_x = I915_BIT_6_SWIZZLE_UNKNOWN;
			swizzle_y = I915_BIT_6_SWIZZLE_UNKNOWN;
		}
	} else {
		/* The 965, G33, and newer, have a very flexible memory
		 * configuration.  It will enable dual-channel mode
		 * (interleaving) on as much memory as it can, and the GPU
		 * will additionally sometimes enable different bit 6
		 * swizzling for tiled objects from the CPU.
		 *
		 * Here's what I found on the G965:
		 *    slot fill         memory size  swizzling
		 * 0A   0B   1A   1B    1-ch   2-ch
		 * 512  0    0    0     512    0     O
		 * 512  0    512  0     16     1008  X
		 * 512  0    0    512   16     1008  X
		 * 0    512  0    512   16     1008  X
		 * 1024 1024 1024 0     2048   1024  O
		 *
		 * We could probably detect this based on either the DRB
		 * matching, which was the case for the swizzling required in
		 * the table above, or from the 1-ch value being less than
		 * the minimum size of a rank.
		 *
		 * Reports indicate that the swizzling actually
		 * varies depending upon page placement inside the
		 * channels, i.e. we see swizzled pages where the
		 * banks of memory are paired and unswizzled on the
		 * uneven portion, so leave that as unknown.
		 */
		if (I915_READ16(C0DRB3) == I915_READ16(C1DRB3)) {
			swizzle_x = I915_BIT_6_SWIZZLE_9_10;
			swizzle_y = I915_BIT_6_SWIZZLE_9;
		}
	}

	if (swizzle_x == I915_BIT_6_SWIZZLE_UNKNOWN ||
	    swizzle_y == I915_BIT_6_SWIZZLE_UNKNOWN) {
		/* Userspace likes to explode if it sees unknown swizzling,
		 * so lie. We will finish the lie when reporting through
		 * the get-tiling-ioctl by reporting the physical swizzle
		 * mode as unknown instead.
		 *
		 * As we don't strictly know what the swizzling is, it may be
		 * bit17 dependent, and so we need to also prevent the pages
		 * from being moved.
		 */
		dev_priv->quirks |= QUIRK_PIN_SWIZZLED_PAGES;
		swizzle_x = I915_BIT_6_SWIZZLE_NONE;
		swizzle_y = I915_BIT_6_SWIZZLE_NONE;
	}

	dev_priv->mm.bit_6_swizzle_x = swizzle_x;
	dev_priv->mm.bit_6_swizzle_y = swizzle_y;
}