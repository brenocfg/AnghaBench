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
#define  BXT_DRAM_RANK_DUAL 129 
 int BXT_DRAM_RANK_MASK ; 
#define  BXT_DRAM_RANK_SINGLE 128 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  bxt_get_dimm_size (int) ; 

__attribute__((used)) static int bxt_get_dimm_ranks(u32 val)
{
	if (!bxt_get_dimm_size(val))
		return 0;

	switch (val & BXT_DRAM_RANK_MASK) {
	case BXT_DRAM_RANK_SINGLE:
		return 1;
	case BXT_DRAM_RANK_DUAL:
		return 2;
	default:
		MISSING_CASE(val);
		return 0;
	}
}