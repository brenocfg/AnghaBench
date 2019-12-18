#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_4__ {char* enc_actions; } ;
struct mlxsw_afa_set {TYPE_2__ ht_key; struct mlxsw_afa_set* next; struct mlxsw_afa_set* prev; } ;
struct mlxsw_afa_block {int cur_act_index; struct mlxsw_afa_set* cur_set; TYPE_1__* afa; scalar_t__ finished; } ;
struct TYPE_3__ {scalar_t__ max_acts_per_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOBUFS ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int MLXSW_AFA_ONE_ACTION_LEN ; 
 int MLXSW_AFA_PAYLOAD_OFFSET ; 
 int /*<<< orphan*/  mlxsw_afa_all_action_type_set (char*,scalar_t__) ; 
 struct mlxsw_afa_set* mlxsw_afa_set_create (int) ; 

__attribute__((used)) static char *mlxsw_afa_block_append_action(struct mlxsw_afa_block *block,
					   u8 action_code, u8 action_size)
{
	char *oneact;
	char *actions;

	if (block->finished)
		return ERR_PTR(-EINVAL);
	if (block->cur_act_index + action_size >
	    block->afa->max_acts_per_set) {
		struct mlxsw_afa_set *set;

		/* The appended action won't fit into the current action set,
		 * so create a new set.
		 */
		set = mlxsw_afa_set_create(false);
		if (!set)
			return ERR_PTR(-ENOBUFS);
		set->prev = block->cur_set;
		block->cur_act_index = 0;
		block->cur_set->next = set;
		block->cur_set = set;
	}

	actions = block->cur_set->ht_key.enc_actions;
	oneact = actions + block->cur_act_index * MLXSW_AFA_ONE_ACTION_LEN;
	block->cur_act_index += action_size;
	mlxsw_afa_all_action_type_set(oneact, action_code);
	return oneact + MLXSW_AFA_PAYLOAD_OFFSET;
}