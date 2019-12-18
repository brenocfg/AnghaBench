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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlxsw_reg_htgt_trap_group { ____Placeholder_mlxsw_reg_htgt_trap_group } mlxsw_reg_htgt_trap_group ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_HPKT_ACK_NOT_REQUIRED ; 
 int /*<<< orphan*/  MLXSW_REG_HPKT_CTRL_PACKET_NO_BUFFER ; 
 int /*<<< orphan*/  MLXSW_REG_HPKT_CTRL_PACKET_USE_BUFFER ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hpkt ; 
 int /*<<< orphan*/  mlxsw_reg_hpkt_ack_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_hpkt_action_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_hpkt_ctrl_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_hpkt_trap_group_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_hpkt_trap_id_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_hpkt_pack(char *payload, u8 action, u16 trap_id,
				       enum mlxsw_reg_htgt_trap_group trap_group,
				       bool is_ctrl)
{
	MLXSW_REG_ZERO(hpkt, payload);
	mlxsw_reg_hpkt_ack_set(payload, MLXSW_REG_HPKT_ACK_NOT_REQUIRED);
	mlxsw_reg_hpkt_action_set(payload, action);
	mlxsw_reg_hpkt_trap_group_set(payload, trap_group);
	mlxsw_reg_hpkt_trap_id_set(payload, trap_id);
	mlxsw_reg_hpkt_ctrl_set(payload, is_ctrl ?
				MLXSW_REG_HPKT_CTRL_PACKET_USE_BUFFER :
				MLXSW_REG_HPKT_CTRL_PACKET_NO_BUFFER);
}