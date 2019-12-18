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
 int /*<<< orphan*/  mlxsw_reg_qpdpm_dscp_entry_e_set (char*,unsigned short,int) ; 
 int /*<<< orphan*/  mlxsw_reg_qpdpm_dscp_entry_prio_set (char*,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
mlxsw_reg_qpdpm_dscp_pack(char *payload, unsigned short dscp, u8 prio)
{
	mlxsw_reg_qpdpm_dscp_entry_e_set(payload, dscp, 1);
	mlxsw_reg_qpdpm_dscp_entry_prio_set(payload, dscp, prio);
}