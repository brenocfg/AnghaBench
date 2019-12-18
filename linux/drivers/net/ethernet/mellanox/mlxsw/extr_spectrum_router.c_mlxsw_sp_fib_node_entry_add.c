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
struct mlxsw_sp_fib_node {int /*<<< orphan*/  entry_list; } ;
struct mlxsw_sp_fib_entry {struct mlxsw_sp_fib_node* fib_node; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_reg_ralue_op { ____Placeholder_mlxsw_reg_ralue_op } mlxsw_reg_ralue_op ;

/* Variables and functions */
 int MLXSW_REG_RALUE_OP_WRITE_DELETE ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  list_is_singular (int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_fib_entry* list_next_entry (struct mlxsw_sp_fib_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_entry_offload_refresh (struct mlxsw_sp_fib_entry*,int,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_fib_entry_update (struct mlxsw_sp*,struct mlxsw_sp_fib_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_node_entry_is_first (struct mlxsw_sp_fib_node*,struct mlxsw_sp_fib_entry*) ; 

__attribute__((used)) static int mlxsw_sp_fib_node_entry_add(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp_fib_entry *fib_entry)
{
	struct mlxsw_sp_fib_node *fib_node = fib_entry->fib_node;

	if (!mlxsw_sp_fib_node_entry_is_first(fib_node, fib_entry))
		return 0;

	/* To prevent packet loss, overwrite the previously offloaded
	 * entry.
	 */
	if (!list_is_singular(&fib_node->entry_list)) {
		enum mlxsw_reg_ralue_op op = MLXSW_REG_RALUE_OP_WRITE_DELETE;
		struct mlxsw_sp_fib_entry *n = list_next_entry(fib_entry, list);

		mlxsw_sp_fib_entry_offload_refresh(n, op, 0);
	}

	return mlxsw_sp_fib_entry_update(mlxsw_sp, fib_entry);
}