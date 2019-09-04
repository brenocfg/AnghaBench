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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_RALUE_ACTION_TYPE_IP2ME ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_action_type_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_ip2me_tunnel_ptr_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_ip2me_v_set (char*,int) ; 

__attribute__((used)) static inline void
mlxsw_reg_ralue_act_ip2me_tun_pack(char *payload, u32 tunnel_ptr)
{
	mlxsw_reg_ralue_action_type_set(payload,
					MLXSW_REG_RALUE_ACTION_TYPE_IP2ME);
	mlxsw_reg_ralue_ip2me_v_set(payload, 1);
	mlxsw_reg_ralue_ip2me_tunnel_ptr_set(payload, tunnel_ptr);
}