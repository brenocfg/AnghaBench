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
typedef  int ushort ;

/* Variables and functions */
 int ASC_IS_EISA ; 
 int ASC_IS_ISA ; 
 int ASC_IS_VL ; 
 unsigned int ASC_MAX_ISA_DMA_COUNT ; 
 unsigned int ASC_MAX_PCI_DMA_COUNT ; 
 unsigned int ASC_MAX_VL_DMA_COUNT ; 

__attribute__((used)) static unsigned int AscGetMaxDmaCount(ushort bus_type)
{
	if (bus_type & ASC_IS_ISA)
		return ASC_MAX_ISA_DMA_COUNT;
	else if (bus_type & (ASC_IS_EISA | ASC_IS_VL))
		return ASC_MAX_VL_DMA_COUNT;
	return ASC_MAX_PCI_DMA_COUNT;
}