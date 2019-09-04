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
struct mv_xor_v2_device {scalar_t__ dma_base; } ;

/* Variables and functions */
 scalar_t__ MV_XOR_V2_DMA_DESQ_DONE_OFF ; 
 int MV_XOR_V2_DMA_DESQ_DONE_PENDING_MASK ; 
 int MV_XOR_V2_DMA_DESQ_DONE_PENDING_SHIFT ; 
 int MV_XOR_V2_DMA_DESQ_DONE_READ_PTR_MASK ; 
 int MV_XOR_V2_DMA_DESQ_DONE_READ_PTR_SHIFT ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline
int mv_xor_v2_get_pending_params(struct mv_xor_v2_device *xor_dev,
				 int *pending_ptr)
{
	u32 reg;

	reg = readl(xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_DONE_OFF);

	/* get the next pending descriptor index */
	*pending_ptr = ((reg >> MV_XOR_V2_DMA_DESQ_DONE_READ_PTR_SHIFT) &
			MV_XOR_V2_DMA_DESQ_DONE_READ_PTR_MASK);

	/* get the number of descriptors pending handle */
	return ((reg >> MV_XOR_V2_DMA_DESQ_DONE_PENDING_SHIFT) &
		MV_XOR_V2_DMA_DESQ_DONE_PENDING_MASK);
}