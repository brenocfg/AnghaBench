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
struct dm_btree_value_type {scalar_t__ inc; } ;
struct dm_array_info {struct dm_btree_value_type value_type; } ;
struct array_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  on_entries (struct dm_array_info*,struct array_block*,scalar_t__) ; 

__attribute__((used)) static void inc_ablock_entries(struct dm_array_info *info, struct array_block *ab)
{
	struct dm_btree_value_type *vt = &info->value_type;

	if (vt->inc)
		on_entries(info, ab, vt->inc);
}