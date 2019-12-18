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
typedef  unsigned long u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  unsigned long u16 ;

/* Variables and functions */
 unsigned long SDMA_AHG_FIELD_LEN_MASK ; 
 unsigned long SDMA_AHG_FIELD_LEN_SHIFT ; 
 unsigned long SDMA_AHG_FIELD_START_MASK ; 
 unsigned long SDMA_AHG_FIELD_START_SHIFT ; 
 unsigned long SDMA_AHG_INDEX_MASK ; 
 unsigned long SDMA_AHG_INDEX_SHIFT ; 
 unsigned long SDMA_AHG_UPDATE_ENABLE_SHIFT ; 
 unsigned long SDMA_AHG_VALUE_MASK ; 
 unsigned long SDMA_AHG_VALUE_SHIFT ; 

__attribute__((used)) static inline u32 sdma_build_ahg_descriptor(
	u16 data,
	u8 dwindex,
	u8 startbit,
	u8 bits)
{
	return (u32)(1UL << SDMA_AHG_UPDATE_ENABLE_SHIFT |
		((startbit & SDMA_AHG_FIELD_START_MASK) <<
		SDMA_AHG_FIELD_START_SHIFT) |
		((bits & SDMA_AHG_FIELD_LEN_MASK) <<
		SDMA_AHG_FIELD_LEN_SHIFT) |
		((dwindex & SDMA_AHG_INDEX_MASK) <<
		SDMA_AHG_INDEX_SHIFT) |
		((data & SDMA_AHG_VALUE_MASK) <<
		SDMA_AHG_VALUE_SHIFT));
}