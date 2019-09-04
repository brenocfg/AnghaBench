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

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_qpdsm_prio_entry_color0_dscp_set (char*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qpdsm_prio_entry_color0_e_set (char*,unsigned short,int) ; 
 int /*<<< orphan*/  mlxsw_reg_qpdsm_prio_entry_color1_dscp_set (char*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qpdsm_prio_entry_color1_e_set (char*,unsigned short,int) ; 
 int /*<<< orphan*/  mlxsw_reg_qpdsm_prio_entry_color2_dscp_set (char*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qpdsm_prio_entry_color2_e_set (char*,unsigned short,int) ; 

__attribute__((used)) static inline void
mlxsw_reg_qpdsm_prio_pack(char *payload, unsigned short prio, u8 dscp)
{
	mlxsw_reg_qpdsm_prio_entry_color0_e_set(payload, prio, 1);
	mlxsw_reg_qpdsm_prio_entry_color0_dscp_set(payload, prio, dscp);
	mlxsw_reg_qpdsm_prio_entry_color1_e_set(payload, prio, 1);
	mlxsw_reg_qpdsm_prio_entry_color1_dscp_set(payload, prio, dscp);
	mlxsw_reg_qpdsm_prio_entry_color2_e_set(payload, prio, 1);
	mlxsw_reg_qpdsm_prio_entry_color2_dscp_set(payload, prio, dscp);
}