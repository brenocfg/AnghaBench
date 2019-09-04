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
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
 unsigned int EDMA_TCD_ATTR_DSIZE_16BIT ; 
 unsigned int EDMA_TCD_ATTR_DSIZE_32BIT ; 
 unsigned int EDMA_TCD_ATTR_DSIZE_64BIT ; 
 unsigned int EDMA_TCD_ATTR_DSIZE_8BIT ; 
 unsigned int EDMA_TCD_ATTR_SSIZE_16BIT ; 
 unsigned int EDMA_TCD_ATTR_SSIZE_32BIT ; 
 unsigned int EDMA_TCD_ATTR_SSIZE_64BIT ; 
 unsigned int EDMA_TCD_ATTR_SSIZE_8BIT ; 

__attribute__((used)) static unsigned int fsl_edma_get_tcd_attr(enum dma_slave_buswidth addr_width)
{
	switch (addr_width) {
	case 1:
		return EDMA_TCD_ATTR_SSIZE_8BIT | EDMA_TCD_ATTR_DSIZE_8BIT;
	case 2:
		return EDMA_TCD_ATTR_SSIZE_16BIT | EDMA_TCD_ATTR_DSIZE_16BIT;
	case 4:
		return EDMA_TCD_ATTR_SSIZE_32BIT | EDMA_TCD_ATTR_DSIZE_32BIT;
	case 8:
		return EDMA_TCD_ATTR_SSIZE_64BIT | EDMA_TCD_ATTR_DSIZE_64BIT;
	default:
		return EDMA_TCD_ATTR_SSIZE_32BIT | EDMA_TCD_ATTR_DSIZE_32BIT;
	}
}