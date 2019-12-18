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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {char* enc_actions; } ;
struct mlxsw_afa_set {TYPE_1__ ht_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_AFA_SET_TYPE_NEXT ; 
 int /*<<< orphan*/  mlxsw_afa_set_next_action_set_ptr_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_set_type_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_afa_set_next_set(struct mlxsw_afa_set *set,
				   u32 next_set_kvdl_index)
{
	char *actions = set->ht_key.enc_actions;

	mlxsw_afa_set_type_set(actions, MLXSW_AFA_SET_TYPE_NEXT);
	mlxsw_afa_set_next_action_set_ptr_set(actions, next_set_kvdl_index);
}