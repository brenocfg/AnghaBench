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
typedef  enum mlxsw_reg_qeec_hr { ____Placeholder_mlxsw_reg_qeec_hr } mlxsw_reg_qeec_hr ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_qeec_element_hierarchy_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_qeec_element_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qeec_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qeec_next_element_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeec ; 

__attribute__((used)) static inline void mlxsw_reg_qeec_pack(char *payload, u8 local_port,
				       enum mlxsw_reg_qeec_hr hr, u8 index,
				       u8 next_index)
{
	MLXSW_REG_ZERO(qeec, payload);
	mlxsw_reg_qeec_local_port_set(payload, local_port);
	mlxsw_reg_qeec_element_hierarchy_set(payload, hr);
	mlxsw_reg_qeec_element_index_set(payload, index);
	mlxsw_reg_qeec_next_element_index_set(payload, next_index);
}