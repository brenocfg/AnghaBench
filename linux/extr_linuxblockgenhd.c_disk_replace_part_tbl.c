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
struct gendisk {int /*<<< orphan*/  part_tbl; } ;
struct disk_part_tbl {int /*<<< orphan*/  last_lookup; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct disk_part_tbl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct disk_part_tbl*) ; 
 struct disk_part_tbl* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_head ; 

__attribute__((used)) static void disk_replace_part_tbl(struct gendisk *disk,
				  struct disk_part_tbl *new_ptbl)
{
	struct disk_part_tbl *old_ptbl =
		rcu_dereference_protected(disk->part_tbl, 1);

	rcu_assign_pointer(disk->part_tbl, new_ptbl);

	if (old_ptbl) {
		rcu_assign_pointer(old_ptbl->last_lookup, NULL);
		kfree_rcu(old_ptbl, rcu_head);
	}
}