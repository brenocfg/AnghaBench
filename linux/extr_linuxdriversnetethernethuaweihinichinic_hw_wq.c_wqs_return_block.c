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
struct hinic_wqs {int /*<<< orphan*/  alloc_blocks_lock; int /*<<< orphan*/  num_free_blks; TYPE_1__* free_blocks; int /*<<< orphan*/  return_blk_pos; } ;
struct TYPE_2__ {int page_idx; int block_idx; } ;

/* Variables and functions */
 int WQS_MAX_NUM_BLOCKS ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wqs_return_block(struct hinic_wqs *wqs, int page_idx,
			     int block_idx)
{
	int pos;

	down(&wqs->alloc_blocks_lock);

	pos = wqs->return_blk_pos++;
	pos &= WQS_MAX_NUM_BLOCKS - 1;

	wqs->free_blocks[pos].page_idx = page_idx;
	wqs->free_blocks[pos].block_idx = block_idx;

	wqs->num_free_blks++;

	up(&wqs->alloc_blocks_lock);
}