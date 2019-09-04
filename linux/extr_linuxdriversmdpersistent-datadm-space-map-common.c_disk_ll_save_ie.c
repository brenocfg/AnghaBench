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
struct ll_disk {int /*<<< orphan*/  bitmap_root; int /*<<< orphan*/  bitmap_info; } ;
struct disk_index_entry {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  __dm_bless_for_disk (struct disk_index_entry*) ; 
 int dm_btree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct disk_index_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int disk_ll_save_ie(struct ll_disk *ll, dm_block_t index,
			   struct disk_index_entry *ie)
{
	__dm_bless_for_disk(ie);
	return dm_btree_insert(&ll->bitmap_info, ll->bitmap_root,
			       &index, ie, &ll->bitmap_root);
}