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
typedef  enum mlxsw_reg_ralxx_protocol { ____Placeholder_mlxsw_reg_ralxx_protocol } mlxsw_reg_ralxx_protocol ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_raltb_protocol_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_raltb_tree_id_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_raltb_virtual_router_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raltb ; 

__attribute__((used)) static inline void mlxsw_reg_raltb_pack(char *payload, u16 virtual_router,
					enum mlxsw_reg_ralxx_protocol protocol,
					u8 tree_id)
{
	MLXSW_REG_ZERO(raltb, payload);
	mlxsw_reg_raltb_virtual_router_set(payload, virtual_router);
	mlxsw_reg_raltb_protocol_set(payload, protocol);
	mlxsw_reg_raltb_tree_id_set(payload, tree_id);
}