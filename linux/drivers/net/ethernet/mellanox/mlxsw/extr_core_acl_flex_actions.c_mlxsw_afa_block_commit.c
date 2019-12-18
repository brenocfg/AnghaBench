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
struct mlxsw_afa_set {int /*<<< orphan*/  kvdl_index; struct mlxsw_afa_set* next; struct mlxsw_afa_set* prev; } ;
struct mlxsw_afa_block {int finished; struct mlxsw_afa_set* first_set; int /*<<< orphan*/  afa; struct mlxsw_afa_set* cur_set; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_afa_set*) ; 
 int PTR_ERR (struct mlxsw_afa_set*) ; 
 struct mlxsw_afa_set* mlxsw_afa_set_get (int /*<<< orphan*/ ,struct mlxsw_afa_set*) ; 
 int /*<<< orphan*/  mlxsw_afa_set_next_set (struct mlxsw_afa_set*,int /*<<< orphan*/ ) ; 

int mlxsw_afa_block_commit(struct mlxsw_afa_block *block)
{
	struct mlxsw_afa_set *set = block->cur_set;
	struct mlxsw_afa_set *prev_set;

	block->cur_set = NULL;
	block->finished = true;

	/* Go over all linked sets starting from last
	 * and try to find existing set in the hash table.
	 * In case it is not there, assign a KVD linear index
	 * and insert it.
	 */
	do {
		prev_set = set->prev;
		set = mlxsw_afa_set_get(block->afa, set);
		if (IS_ERR(set))
			/* No rollback is needed since the chain is
			 * in consistent state and mlxsw_afa_block_destroy
			 * will take care of putting it away.
			 */
			return PTR_ERR(set);
		if (prev_set) {
			prev_set->next = set;
			mlxsw_afa_set_next_set(prev_set, set->kvdl_index);
			set = prev_set;
		}
	} while (prev_set);

	block->first_set = set;
	return 0;
}