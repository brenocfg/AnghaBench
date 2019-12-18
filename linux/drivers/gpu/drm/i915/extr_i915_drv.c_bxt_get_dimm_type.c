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
typedef  enum intel_dram_type { ____Placeholder_intel_dram_type } intel_dram_type ;

/* Variables and functions */
#define  BXT_DRAM_TYPE_DDR3 131 
#define  BXT_DRAM_TYPE_DDR4 130 
#define  BXT_DRAM_TYPE_LPDDR3 129 
#define  BXT_DRAM_TYPE_LPDDR4 128 
 int BXT_DRAM_TYPE_MASK ; 
 int INTEL_DRAM_DDR3 ; 
 int INTEL_DRAM_DDR4 ; 
 int INTEL_DRAM_LPDDR3 ; 
 int INTEL_DRAM_LPDDR4 ; 
 int INTEL_DRAM_UNKNOWN ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  bxt_get_dimm_size (int) ; 

__attribute__((used)) static enum intel_dram_type bxt_get_dimm_type(u32 val)
{
	if (!bxt_get_dimm_size(val))
		return INTEL_DRAM_UNKNOWN;

	switch (val & BXT_DRAM_TYPE_MASK) {
	case BXT_DRAM_TYPE_DDR3:
		return INTEL_DRAM_DDR3;
	case BXT_DRAM_TYPE_LPDDR3:
		return INTEL_DRAM_LPDDR3;
	case BXT_DRAM_TYPE_DDR4:
		return INTEL_DRAM_DDR4;
	case BXT_DRAM_TYPE_LPDDR4:
		return INTEL_DRAM_LPDDR4;
	default:
		MISSING_CASE(val);
		return INTEL_DRAM_UNKNOWN;
	}
}