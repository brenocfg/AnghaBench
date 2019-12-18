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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
typedef  enum intel_dram_type { ____Placeholder_intel_dram_type } intel_dram_type ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_DRAM_DDR3 ; 
 int INTEL_DRAM_DDR4 ; 
 int INTEL_DRAM_LPDDR3 ; 
 int INTEL_DRAM_LPDDR4 ; 
 int INTEL_DRAM_UNKNOWN ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  SKL_DRAM_DDR_TYPE_DDR3 131 
#define  SKL_DRAM_DDR_TYPE_DDR4 130 
#define  SKL_DRAM_DDR_TYPE_LPDDR3 129 
#define  SKL_DRAM_DDR_TYPE_LPDDR4 128 
 int SKL_DRAM_DDR_TYPE_MASK ; 
 int /*<<< orphan*/  SKL_MAD_INTER_CHANNEL_0_0_0_MCHBAR_MCMAIN ; 

__attribute__((used)) static enum intel_dram_type
skl_get_dram_type(struct drm_i915_private *dev_priv)
{
	u32 val;

	val = I915_READ(SKL_MAD_INTER_CHANNEL_0_0_0_MCHBAR_MCMAIN);

	switch (val & SKL_DRAM_DDR_TYPE_MASK) {
	case SKL_DRAM_DDR_TYPE_DDR3:
		return INTEL_DRAM_DDR3;
	case SKL_DRAM_DDR_TYPE_DDR4:
		return INTEL_DRAM_DDR4;
	case SKL_DRAM_DDR_TYPE_LPDDR3:
		return INTEL_DRAM_LPDDR3;
	case SKL_DRAM_DDR_TYPE_LPDDR4:
		return INTEL_DRAM_LPDDR4;
	default:
		MISSING_CASE(val);
		return INTEL_DRAM_UNKNOWN;
	}
}