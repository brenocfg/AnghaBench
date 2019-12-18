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
 int /*<<< orphan*/  MLXSW_REG_QEEC_HIERARCY_PORT ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_qeec_element_hierarchy_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qeec_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qeec_ptps_set (char*,int) ; 
 int /*<<< orphan*/  qeec ; 

__attribute__((used)) static inline void mlxsw_reg_qeec_ptps_pack(char *payload, u8 local_port,
					    bool ptps)
{
	MLXSW_REG_ZERO(qeec, payload);
	mlxsw_reg_qeec_local_port_set(payload, local_port);
	mlxsw_reg_qeec_element_hierarchy_set(payload,
					     MLXSW_REG_QEEC_HIERARCY_PORT);
	mlxsw_reg_qeec_ptps_set(payload, ptps);
}