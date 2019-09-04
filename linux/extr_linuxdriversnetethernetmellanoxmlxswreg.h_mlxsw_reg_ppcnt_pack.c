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
typedef  enum mlxsw_reg_ppcnt_grp { ____Placeholder_mlxsw_reg_ppcnt_grp } mlxsw_reg_ppcnt_grp ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ppcnt_clr_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ppcnt_grp_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ppcnt_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ppcnt_pnat_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ppcnt_prio_tc_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ppcnt_swid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppcnt ; 

__attribute__((used)) static inline void mlxsw_reg_ppcnt_pack(char *payload, u8 local_port,
					enum mlxsw_reg_ppcnt_grp grp,
					u8 prio_tc)
{
	MLXSW_REG_ZERO(ppcnt, payload);
	mlxsw_reg_ppcnt_swid_set(payload, 0);
	mlxsw_reg_ppcnt_local_port_set(payload, local_port);
	mlxsw_reg_ppcnt_pnat_set(payload, 0);
	mlxsw_reg_ppcnt_grp_set(payload, grp);
	mlxsw_reg_ppcnt_clr_set(payload, 0);
	mlxsw_reg_ppcnt_prio_tc_set(payload, prio_tc);
}