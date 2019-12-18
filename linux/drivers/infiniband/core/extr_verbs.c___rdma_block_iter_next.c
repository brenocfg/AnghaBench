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
struct ib_block_iter {int __dma_addr; int __sg_advance; int /*<<< orphan*/  __sg_nents; scalar_t__ __sg; int /*<<< orphan*/  __pg_bit; } ;

/* Variables and functions */
 unsigned int BIT_ULL (int /*<<< orphan*/ ) ; 
 int sg_dma_address (scalar_t__) ; 
 scalar_t__ sg_dma_len (scalar_t__) ; 
 scalar_t__ sg_next (scalar_t__) ; 

bool __rdma_block_iter_next(struct ib_block_iter *biter)
{
	unsigned int block_offset;

	if (!biter->__sg_nents || !biter->__sg)
		return false;

	biter->__dma_addr = sg_dma_address(biter->__sg) + biter->__sg_advance;
	block_offset = biter->__dma_addr & (BIT_ULL(biter->__pg_bit) - 1);
	biter->__sg_advance += BIT_ULL(biter->__pg_bit) - block_offset;

	if (biter->__sg_advance >= sg_dma_len(biter->__sg)) {
		biter->__sg_advance = 0;
		biter->__sg = sg_next(biter->__sg);
		biter->__sg_nents--;
	}

	return true;
}