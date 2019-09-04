#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int max_blocks; int flags; int empty_slots; int /*<<< orphan*/  empty_list; TYPE_2__* block; int /*<<< orphan*/  taken_list; int /*<<< orphan*/  free_list; } ;
typedef  TYPE_1__ rh_info_t ;
struct TYPE_9__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_2__ rh_block_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int RHIF_STATIC_BLOCK ; 
 int /*<<< orphan*/  fixup (unsigned long,unsigned long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 

__attribute__((used)) static int grow(rh_info_t * info, int max_blocks)
{
	rh_block_t *block, *blk;
	int i, new_blocks;
	int delta;
	unsigned long blks, blke;

	if (max_blocks <= info->max_blocks)
		return -EINVAL;

	new_blocks = max_blocks - info->max_blocks;

	block = kmalloc_array(max_blocks, sizeof(rh_block_t), GFP_ATOMIC);
	if (block == NULL)
		return -ENOMEM;

	if (info->max_blocks > 0) {

		/* copy old block area */
		memcpy(block, info->block,
		       sizeof(rh_block_t) * info->max_blocks);

		delta = (char *)block - (char *)info->block;

		/* and fixup list pointers */
		blks = (unsigned long)info->block;
		blke = (unsigned long)(info->block + info->max_blocks);

		for (i = 0, blk = block; i < info->max_blocks; i++, blk++)
			fixup(blks, blke, delta, &blk->list);

		fixup(blks, blke, delta, &info->empty_list);
		fixup(blks, blke, delta, &info->free_list);
		fixup(blks, blke, delta, &info->taken_list);

		/* free the old allocated memory */
		if ((info->flags & RHIF_STATIC_BLOCK) == 0)
			kfree(info->block);
	}

	info->block = block;
	info->empty_slots += new_blocks;
	info->max_blocks = max_blocks;
	info->flags &= ~RHIF_STATIC_BLOCK;

	/* add all new blocks to the free list */
	blk = block + info->max_blocks - new_blocks;
	for (i = 0; i < new_blocks; i++, blk++)
		list_add(&blk->list, &info->empty_list);

	return 0;
}