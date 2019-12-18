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

/* Variables and functions */
 int BXT_DRAM_WIDTH_MASK ; 
 int BXT_DRAM_WIDTH_SHIFT ; 
 int /*<<< orphan*/  bxt_get_dimm_size (int) ; 

__attribute__((used)) static int bxt_get_dimm_width(u32 val)
{
	if (!bxt_get_dimm_size(val))
		return 0;

	val = (val & BXT_DRAM_WIDTH_MASK) >> BXT_DRAM_WIDTH_SHIFT;

	return 8 << val;
}