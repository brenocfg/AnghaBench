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
typedef  unsigned long long u64 ;
typedef  scalar_t__ current_block_end ;

/* Variables and functions */
 unsigned long long alignment_of (unsigned long long) ; 

__attribute__((used)) static int mlx4_ib_umem_calc_block_mtt(u64 next_block_start,
				       u64 current_block_end,
				       u64 block_shift)
{
	/* Check whether the alignment of the new block is aligned as well as
	 * the previous block.
	 * Block address must start with zeros till size of entity_size.
	 */
	if ((next_block_start & ((1ULL << block_shift) - 1ULL)) != 0)
		/*
		 * It is not as well aligned as the previous block-reduce the
		 * mtt size accordingly. Here we take the last right bit which
		 * is 1.
		 */
		block_shift = alignment_of(next_block_start);

	/*
	 * Check whether the alignment of the end of previous block - is it
	 * aligned as well as the start of the block
	 */
	if (((current_block_end) & ((1ULL << block_shift) - 1ULL)) != 0)
		/*
		 * It is not as well aligned as the start of the block -
		 * reduce the mtt size accordingly.
		 */
		block_shift = alignment_of(current_block_end);

	return block_shift;
}