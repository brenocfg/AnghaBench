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
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlxsw_reg_rmft2_irif_mask { ____Placeholder_mlxsw_reg_rmft2_irif_mask } mlxsw_reg_rmft2_irif_mask ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_RMFT2_OP_READ_WRITE ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_flexible_action_set_memcpy_to (char*,char const*) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_irif_mask_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_irif_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_offset_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_op_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_v_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_virtual_router_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmft2 ; 

__attribute__((used)) static inline void
mlxsw_reg_rmft2_common_pack(char *payload, bool v, u16 offset,
			    u16 virtual_router,
			    enum mlxsw_reg_rmft2_irif_mask irif_mask, u16 irif,
			    const char *flex_action_set)
{
	MLXSW_REG_ZERO(rmft2, payload);
	mlxsw_reg_rmft2_v_set(payload, v);
	mlxsw_reg_rmft2_op_set(payload, MLXSW_REG_RMFT2_OP_READ_WRITE);
	mlxsw_reg_rmft2_offset_set(payload, offset);
	mlxsw_reg_rmft2_virtual_router_set(payload, virtual_router);
	mlxsw_reg_rmft2_irif_mask_set(payload, irif_mask);
	mlxsw_reg_rmft2_irif_set(payload, irif);
	if (flex_action_set)
		mlxsw_reg_rmft2_flexible_action_set_memcpy_to(payload,
							      flex_action_set);
}