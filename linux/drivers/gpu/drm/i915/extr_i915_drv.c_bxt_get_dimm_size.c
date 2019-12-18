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
#define  BXT_DRAM_SIZE_12GBIT 132 
#define  BXT_DRAM_SIZE_16GBIT 131 
#define  BXT_DRAM_SIZE_4GBIT 130 
#define  BXT_DRAM_SIZE_6GBIT 129 
#define  BXT_DRAM_SIZE_8GBIT 128 
 int BXT_DRAM_SIZE_MASK ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 

__attribute__((used)) static int bxt_get_dimm_size(u32 val)
{
	switch (val & BXT_DRAM_SIZE_MASK) {
	case BXT_DRAM_SIZE_4GBIT:
		return 4;
	case BXT_DRAM_SIZE_6GBIT:
		return 6;
	case BXT_DRAM_SIZE_8GBIT:
		return 8;
	case BXT_DRAM_SIZE_12GBIT:
		return 12;
	case BXT_DRAM_SIZE_16GBIT:
		return 16;
	default:
		MISSING_CASE(val);
		return 0;
	}
}