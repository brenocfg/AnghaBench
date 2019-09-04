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
struct coh901318_pool {int dummy; } ;
struct coh901318_lli {int control; size_t src_addr; size_t dst_addr; scalar_t__ link_addr; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 int DMA_DEV_TO_MEM ; 
 int DMA_MEM_TO_DEV ; 
 int EINVAL ; 
 int MAX_DMA_PACKET_SIZE ; 
 struct coh901318_lli* coh901318_lli_next (struct coh901318_lli*) ; 

int
coh901318_lli_fill_single(struct coh901318_pool *pool,
			  struct coh901318_lli *lli,
			  dma_addr_t buf, unsigned int size,
			  dma_addr_t dev_addr, u32 ctrl_chained, u32 ctrl_eom,
			  enum dma_transfer_direction dir)
{
	int s = size;
	dma_addr_t src;
	dma_addr_t dst;


	if (dir == DMA_MEM_TO_DEV) {
		src = buf;
		dst = dev_addr;

	} else if (dir == DMA_DEV_TO_MEM) {

		src = dev_addr;
		dst = buf;
	} else {
		return -EINVAL;
	}

	while (lli->link_addr) {
		size_t block_size = MAX_DMA_PACKET_SIZE;
		lli->control = ctrl_chained | MAX_DMA_PACKET_SIZE;

		/* If we are on the next-to-final block and there will
		 * be less than half a DMA packet left for the last
		 * block, then we want to make this block a little
		 * smaller to balance the sizes. This is meant to
		 * avoid too small transfers if the buffer size is
		 * (MAX_DMA_PACKET_SIZE*N + 1) */
		if (s < (MAX_DMA_PACKET_SIZE + MAX_DMA_PACKET_SIZE/2))
			block_size = MAX_DMA_PACKET_SIZE/2;

		s -= block_size;
		lli->src_addr = src;
		lli->dst_addr = dst;

		lli = coh901318_lli_next(lli);

		if (dir == DMA_MEM_TO_DEV)
			src += block_size;
		else if (dir == DMA_DEV_TO_MEM)
			dst += block_size;
	}

	lli->control = ctrl_eom | s;
	lli->src_addr = src;
	lli->dst_addr = dst;

	return 0;
}