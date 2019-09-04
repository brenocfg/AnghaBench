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
struct mlxsw_sp_span_entry {scalar_t__ ref_count; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_sp_span_entry_destroy (struct mlxsw_sp_span_entry*) ; 

__attribute__((used)) static int mlxsw_sp_span_entry_put(struct mlxsw_sp *mlxsw_sp,
				   struct mlxsw_sp_span_entry *span_entry)
{
	WARN_ON(!span_entry->ref_count);
	if (--span_entry->ref_count == 0)
		mlxsw_sp_span_entry_destroy(span_entry);
	return 0;
}