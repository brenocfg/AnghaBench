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
struct hinic_wqs {int num_pages; int return_blk_pos; int num_free_blks; int /*<<< orphan*/  alloc_blocks_lock; scalar_t__ alloc_blk_pos; TYPE_1__* free_blocks; } ;
struct TYPE_2__ {int page_idx; int block_idx; } ;

/* Variables and functions */
 int WQS_BLOCKS_PER_PAGE ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void init_wqs_blocks_arr(struct hinic_wqs *wqs)
{
	int page_idx, blk_idx, pos = 0;

	for (page_idx = 0; page_idx < wqs->num_pages; page_idx++) {
		for (blk_idx = 0; blk_idx < WQS_BLOCKS_PER_PAGE; blk_idx++) {
			wqs->free_blocks[pos].page_idx = page_idx;
			wqs->free_blocks[pos].block_idx = blk_idx;
			pos++;
		}
	}

	wqs->alloc_blk_pos = 0;
	wqs->return_blk_pos = pos;
	wqs->num_free_blks = pos;

	sema_init(&wqs->alloc_blocks_lock, 1);
}