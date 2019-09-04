#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int alignment; int max_blocks; int empty_slots; int flags; int /*<<< orphan*/  empty_list; int /*<<< orphan*/  taken_list; int /*<<< orphan*/  free_list; TYPE_2__* block; } ;
typedef  TYPE_1__ rh_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_2__ rh_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int RHIF_STATIC_BLOCK ; 
 int RHIF_STATIC_INFO ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void rh_init(rh_info_t * info, unsigned int alignment, int max_blocks,
	     rh_block_t * block)
{
	int i;
	rh_block_t *blk;

	/* Alignment must be a power of two */
	if ((alignment & (alignment - 1)) != 0)
		return;

	info->alignment = alignment;

	/* Initially everything as empty */
	info->block = block;
	info->max_blocks = max_blocks;
	info->empty_slots = max_blocks;
	info->flags = RHIF_STATIC_INFO | RHIF_STATIC_BLOCK;

	INIT_LIST_HEAD(&info->empty_list);
	INIT_LIST_HEAD(&info->free_list);
	INIT_LIST_HEAD(&info->taken_list);

	/* Add all new blocks to the free list */
	for (i = 0, blk = block; i < max_blocks; i++, blk++)
		list_add(&blk->list, &info->empty_list);
}