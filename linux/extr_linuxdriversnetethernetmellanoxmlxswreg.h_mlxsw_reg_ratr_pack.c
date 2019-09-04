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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlxsw_reg_ratr_type { ____Placeholder_mlxsw_reg_ratr_type } mlxsw_reg_ratr_type ;
typedef  enum mlxsw_reg_ratr_op { ____Placeholder_mlxsw_reg_ratr_op } mlxsw_reg_ratr_op ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ratr_adjacency_index_high_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ratr_adjacency_index_low_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ratr_egress_router_interface_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ratr_op_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ratr_type_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ratr_v_set (char*,int) ; 
 int /*<<< orphan*/  ratr ; 

__attribute__((used)) static inline void
mlxsw_reg_ratr_pack(char *payload,
		    enum mlxsw_reg_ratr_op op, bool valid,
		    enum mlxsw_reg_ratr_type type,
		    u32 adjacency_index, u16 egress_rif)
{
	MLXSW_REG_ZERO(ratr, payload);
	mlxsw_reg_ratr_op_set(payload, op);
	mlxsw_reg_ratr_v_set(payload, valid);
	mlxsw_reg_ratr_type_set(payload, type);
	mlxsw_reg_ratr_adjacency_index_low_set(payload, adjacency_index);
	mlxsw_reg_ratr_adjacency_index_high_set(payload, adjacency_index >> 16);
	mlxsw_reg_ratr_egress_router_interface_set(payload, egress_rif);
}