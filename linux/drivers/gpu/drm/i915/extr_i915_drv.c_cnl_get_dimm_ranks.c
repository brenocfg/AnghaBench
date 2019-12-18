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
 int CNL_DRAM_RANK_MASK ; 
 int CNL_DRAM_RANK_SHIFT ; 
 scalar_t__ cnl_get_dimm_size (int) ; 

__attribute__((used)) static int cnl_get_dimm_ranks(u16 val)
{
	if (cnl_get_dimm_size(val) == 0)
		return 0;

	val = (val & CNL_DRAM_RANK_MASK) >> CNL_DRAM_RANK_SHIFT;

	return val + 1;
}