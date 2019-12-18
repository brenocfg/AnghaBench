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
typedef  int /*<<< orphan*/  uint64_t ;
struct resize {int /*<<< orphan*/  root; TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  btree_info; } ;

/* Variables and functions */
 int dm_btree_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drop_blocks(struct resize *resize, unsigned begin_index,
		       unsigned end_index)
{
	int r;

	while (begin_index != end_index) {
		uint64_t key = begin_index++;
		r = dm_btree_remove(&resize->info->btree_info, resize->root,
				    &key, &resize->root);
		if (r)
			return r;
	}

	return 0;
}