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
struct pending_block {int vec_cnt; struct pending_block* data; TYPE_1__* vecs; } ;
struct log_writes_c {int dummy; } ;
struct TYPE_2__ {scalar_t__ bv_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct pending_block*) ; 
 int /*<<< orphan*/  put_pending_block (struct log_writes_c*) ; 

__attribute__((used)) static void free_pending_block(struct log_writes_c *lc,
			       struct pending_block *block)
{
	int i;

	for (i = 0; i < block->vec_cnt; i++) {
		if (block->vecs[i].bv_page)
			__free_page(block->vecs[i].bv_page);
	}
	kfree(block->data);
	kfree(block);
	put_pending_block(lc);
}