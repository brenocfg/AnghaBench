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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {char* enc_actions; } ;
struct mlxsw_afa_set {TYPE_1__ ht_key; } ;
typedef  enum mlxsw_afa_set_goto_binding_cmd { ____Placeholder_mlxsw_afa_set_goto_binding_cmd } mlxsw_afa_set_goto_binding_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_AFA_SET_TYPE_GOTO ; 
 int /*<<< orphan*/  mlxsw_afa_set_goto_binding_cmd_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_afa_set_goto_g_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_afa_set_goto_next_binding_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_set_type_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_afa_set_goto_set(struct mlxsw_afa_set *set,
				   enum mlxsw_afa_set_goto_binding_cmd cmd,
				   u16 group_id)
{
	char *actions = set->ht_key.enc_actions;

	mlxsw_afa_set_type_set(actions, MLXSW_AFA_SET_TYPE_GOTO);
	mlxsw_afa_set_goto_g_set(actions, true);
	mlxsw_afa_set_goto_binding_cmd_set(actions, cmd);
	mlxsw_afa_set_goto_next_binding_set(actions, group_id);
}