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
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlxsw_reg_ralxx_protocol { ____Placeholder_mlxsw_reg_ralxx_protocol } mlxsw_reg_ralxx_protocol ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_raleu_adjacency_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_raleu_ecmp_size_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_raleu_new_adjacency_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_raleu_new_ecmp_size_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_raleu_protocol_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_raleu_virtual_router_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raleu ; 

__attribute__((used)) static inline void mlxsw_reg_raleu_pack(char *payload,
					enum mlxsw_reg_ralxx_protocol protocol,
					u16 virtual_router,
					u32 adjacency_index, u16 ecmp_size,
					u32 new_adjacency_index,
					u16 new_ecmp_size)
{
	MLXSW_REG_ZERO(raleu, payload);
	mlxsw_reg_raleu_protocol_set(payload, protocol);
	mlxsw_reg_raleu_virtual_router_set(payload, virtual_router);
	mlxsw_reg_raleu_adjacency_index_set(payload, adjacency_index);
	mlxsw_reg_raleu_ecmp_size_set(payload, ecmp_size);
	mlxsw_reg_raleu_new_adjacency_index_set(payload, new_adjacency_index);
	mlxsw_reg_raleu_new_ecmp_size_set(payload, new_ecmp_size);
}