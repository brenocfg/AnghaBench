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
struct mlxsw_sp_span_entry {int id; scalar_t__ ref_count; } ;
struct TYPE_2__ {int entries_count; struct mlxsw_sp_span_entry* entries; } ;
struct mlxsw_sp {TYPE_1__ span; } ;

/* Variables and functions */

__attribute__((used)) static struct mlxsw_sp_span_entry *
mlxsw_sp_span_entry_find_by_id(struct mlxsw_sp *mlxsw_sp, int span_id)
{
	int i;

	for (i = 0; i < mlxsw_sp->span.entries_count; i++) {
		struct mlxsw_sp_span_entry *curr = &mlxsw_sp->span.entries[i];

		if (curr->ref_count && curr->id == span_id)
			return curr;
	}
	return NULL;
}