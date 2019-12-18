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
struct NFTLrecord {unsigned int* ReplUnitTable; unsigned int nb_blocks; } ;

/* Variables and functions */
 unsigned int BLOCK_FREE ; 
 unsigned int BLOCK_NIL ; 
 unsigned int BLOCK_RESERVED ; 
 scalar_t__ NFTL_formatblock (struct NFTLrecord*,unsigned int) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 

__attribute__((used)) static void format_chain(struct NFTLrecord *nftl, unsigned int first_block)
{
	unsigned int block = first_block, block1;

	printk("Formatting chain at block %d\n", first_block);

	for (;;) {
		block1 = nftl->ReplUnitTable[block];

		printk("Formatting block %d\n", block);
		if (NFTL_formatblock(nftl, block) < 0) {
			/* cannot format !!!! Mark it as Bad Unit */
			nftl->ReplUnitTable[block] = BLOCK_RESERVED;
		} else {
			nftl->ReplUnitTable[block] = BLOCK_FREE;
		}

		/* goto next block on the chain */
		block = block1;

		if (!(block == BLOCK_NIL || block < nftl->nb_blocks))
			printk("incorrect ReplUnitTable[] : %d\n", block);
		if (block == BLOCK_NIL || block >= nftl->nb_blocks)
			break;
	}
}