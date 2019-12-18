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
typedef  enum mlxsw_reg_pxbt_op { ____Placeholder_mlxsw_reg_pxbt_op } mlxsw_reg_pxbt_op ;
typedef  enum mlxsw_reg_pxbt_e { ____Placeholder_mlxsw_reg_pxbt_e } mlxsw_reg_pxbt_e ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ppbt_acl_info_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ppbt_e_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ppbt_g_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ppbt_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ppbt_op_set (char*,int) ; 
 int /*<<< orphan*/  ppbt ; 

__attribute__((used)) static inline void mlxsw_reg_ppbt_pack(char *payload, enum mlxsw_reg_pxbt_e e,
				       enum mlxsw_reg_pxbt_op op,
				       u8 local_port, u16 acl_info)
{
	MLXSW_REG_ZERO(ppbt, payload);
	mlxsw_reg_ppbt_e_set(payload, e);
	mlxsw_reg_ppbt_op_set(payload, op);
	mlxsw_reg_ppbt_local_port_set(payload, local_port);
	mlxsw_reg_ppbt_g_set(payload, true);
	mlxsw_reg_ppbt_acl_info_set(payload, acl_info);
}