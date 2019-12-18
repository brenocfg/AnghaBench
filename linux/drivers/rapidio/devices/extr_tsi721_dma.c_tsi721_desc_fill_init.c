#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct tsi721_tx_desc {int rtype; int destid; int rio_addr; int rio_addr_u; } ;
struct TYPE_2__ {scalar_t__ s_size; scalar_t__ s_dist; void* bufptr_hi; void* bufptr_lo; } ;
struct tsi721_dma_desc {TYPE_1__ t1; void* raddr_hi; void* raddr_lo; void* bcount; void* type_id; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int DTYPE1 ; 
 int EINVAL ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ sg_dma_address (struct scatterlist*) ; 

__attribute__((used)) static int
tsi721_desc_fill_init(struct tsi721_tx_desc *desc,
		      struct tsi721_dma_desc *bd_ptr,
		      struct scatterlist *sg, u32 sys_size)
{
	u64 rio_addr;

	if (!bd_ptr)
		return -EINVAL;

	/* Initialize DMA descriptor */
	bd_ptr->type_id = cpu_to_le32((DTYPE1 << 29) |
				      (desc->rtype << 19) | desc->destid);
	bd_ptr->bcount = cpu_to_le32(((desc->rio_addr & 0x3) << 30) |
				     (sys_size << 26));
	rio_addr = (desc->rio_addr >> 2) |
				((u64)(desc->rio_addr_u & 0x3) << 62);
	bd_ptr->raddr_lo = cpu_to_le32(rio_addr & 0xffffffff);
	bd_ptr->raddr_hi = cpu_to_le32(rio_addr >> 32);
	bd_ptr->t1.bufptr_lo = cpu_to_le32(
					(u64)sg_dma_address(sg) & 0xffffffff);
	bd_ptr->t1.bufptr_hi = cpu_to_le32((u64)sg_dma_address(sg) >> 32);
	bd_ptr->t1.s_dist = 0;
	bd_ptr->t1.s_size = 0;

	return 0;
}