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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int SKL_DRAM_WIDTH_MASK ; 
 int SKL_DRAM_WIDTH_SHIFT ; 
#define  SKL_DRAM_WIDTH_X16 130 
#define  SKL_DRAM_WIDTH_X32 129 
#define  SKL_DRAM_WIDTH_X8 128 
 scalar_t__ skl_get_dimm_size (int) ; 

__attribute__((used)) static int skl_get_dimm_width(u16 val)
{
	if (skl_get_dimm_size(val) == 0)
		return 0;

	switch (val & SKL_DRAM_WIDTH_MASK) {
	case SKL_DRAM_WIDTH_X8:
	case SKL_DRAM_WIDTH_X16:
	case SKL_DRAM_WIDTH_X32:
		val = (val & SKL_DRAM_WIDTH_MASK) >> SKL_DRAM_WIDTH_SHIFT;
		return 8 << val;
	default:
		MISSING_CASE(val);
		return 0;
	}
}