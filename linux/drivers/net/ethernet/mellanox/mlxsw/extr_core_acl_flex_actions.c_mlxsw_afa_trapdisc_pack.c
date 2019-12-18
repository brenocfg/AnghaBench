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
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlxsw_afa_trapdisc_trap_action { ____Placeholder_mlxsw_afa_trapdisc_trap_action } mlxsw_afa_trapdisc_trap_action ;
typedef  enum mlxsw_afa_trapdisc_forward_action { ____Placeholder_mlxsw_afa_trapdisc_forward_action } mlxsw_afa_trapdisc_forward_action ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_afa_trapdisc_forward_action_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_afa_trapdisc_trap_action_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_afa_trapdisc_trap_id_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
mlxsw_afa_trapdisc_pack(char *payload,
			enum mlxsw_afa_trapdisc_trap_action trap_action,
			enum mlxsw_afa_trapdisc_forward_action forward_action,
			u16 trap_id)
{
	mlxsw_afa_trapdisc_trap_action_set(payload, trap_action);
	mlxsw_afa_trapdisc_forward_action_set(payload, forward_action);
	mlxsw_afa_trapdisc_trap_id_set(payload, trap_id);
}