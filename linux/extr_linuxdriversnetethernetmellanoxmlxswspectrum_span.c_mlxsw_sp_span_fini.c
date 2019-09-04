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
struct mlxsw_sp_span_entry {int /*<<< orphan*/  bound_ports_list; } ;
struct TYPE_2__ {int entries_count; struct mlxsw_sp_span_entry* entries; } ;
struct mlxsw_sp {TYPE_1__ span; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_span_entry*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void mlxsw_sp_span_fini(struct mlxsw_sp *mlxsw_sp)
{
	int i;

	for (i = 0; i < mlxsw_sp->span.entries_count; i++) {
		struct mlxsw_sp_span_entry *curr = &mlxsw_sp->span.entries[i];

		WARN_ON_ONCE(!list_empty(&curr->bound_ports_list));
	}
	kfree(mlxsw_sp->span.entries);
}