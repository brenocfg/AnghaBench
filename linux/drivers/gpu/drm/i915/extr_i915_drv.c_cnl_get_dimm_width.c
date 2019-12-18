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
 int CNL_DRAM_WIDTH_MASK ; 
 int CNL_DRAM_WIDTH_SHIFT ; 
#define  CNL_DRAM_WIDTH_X16 130 
#define  CNL_DRAM_WIDTH_X32 129 
#define  CNL_DRAM_WIDTH_X8 128 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 scalar_t__ cnl_get_dimm_size (int) ; 

__attribute__((used)) static int cnl_get_dimm_width(u16 val)
{
	if (cnl_get_dimm_size(val) == 0)
		return 0;

	switch (val & CNL_DRAM_WIDTH_MASK) {
	case CNL_DRAM_WIDTH_X8:
	case CNL_DRAM_WIDTH_X16:
	case CNL_DRAM_WIDTH_X32:
		val = (val & CNL_DRAM_WIDTH_MASK) >> CNL_DRAM_WIDTH_SHIFT;
		return 8 << val;
	default:
		MISSING_CASE(val);
		return 0;
	}
}