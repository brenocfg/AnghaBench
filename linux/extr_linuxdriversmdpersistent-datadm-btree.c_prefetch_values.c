#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value_le ;
struct dm_btree_cursor {int depth; TYPE_2__* info; struct cursor_node* nodes; } ;
struct dm_block_manager {int dummy; } ;
struct cursor_node {int /*<<< orphan*/  b; } ;
struct TYPE_6__ {int /*<<< orphan*/  nr_entries; } ;
struct btree_node {TYPE_3__ header; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_4__ {int size; } ;
struct TYPE_5__ {TYPE_1__ value_type; int /*<<< orphan*/  tm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct btree_node* dm_block_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_bm_prefetch (struct dm_block_manager*,int /*<<< orphan*/ ) ; 
 struct dm_block_manager* dm_tm_get_bm (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  value_ptr (struct btree_node*,unsigned int) ; 

__attribute__((used)) static void prefetch_values(struct dm_btree_cursor *c)
{
	unsigned i, nr;
	__le64 value_le;
	struct cursor_node *n = c->nodes + c->depth - 1;
	struct btree_node *bn = dm_block_data(n->b);
	struct dm_block_manager *bm = dm_tm_get_bm(c->info->tm);

	BUG_ON(c->info->value_type.size != sizeof(value_le));

	nr = le32_to_cpu(bn->header.nr_entries);
	for (i = 0; i < nr; i++) {
		memcpy(&value_le, value_ptr(bn, i), sizeof(value_le));
		dm_bm_prefetch(bm, le64_to_cpu(value_le));
	}
}