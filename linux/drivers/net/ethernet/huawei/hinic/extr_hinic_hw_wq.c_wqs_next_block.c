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
struct hinic_wqs {scalar_t__ num_free_blks; int /*<<< orphan*/  alloc_blocks_lock; TYPE_1__* free_blocks; int /*<<< orphan*/  alloc_blk_pos; } ;
struct TYPE_2__ {int page_idx; int block_idx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int WQS_MAX_NUM_BLOCKS ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wqs_next_block(struct hinic_wqs *wqs, int *page_idx,
			  int *block_idx)
{
	int pos;

	down(&wqs->alloc_blocks_lock);

	wqs->num_free_blks--;

	if (wqs->num_free_blks < 0) {
		wqs->num_free_blks++;
		up(&wqs->alloc_blocks_lock);
		return -ENOMEM;
	}

	pos = wqs->alloc_blk_pos++;
	pos &= WQS_MAX_NUM_BLOCKS - 1;

	*page_idx = wqs->free_blocks[pos].page_idx;
	*block_idx = wqs->free_blocks[pos].block_idx;

	wqs->free_blocks[pos].page_idx = -1;
	wqs->free_blocks[pos].block_idx = -1;

	up(&wqs->alloc_blocks_lock);
	return 0;
}