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
typedef  enum mlxsw_reg_rmft2_irif_mask { ____Placeholder_mlxsw_reg_rmft2_irif_mask } mlxsw_reg_rmft2_irif_mask ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_RMFT2_TYPE_IPV4 ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_common_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_dip4_mask_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_dip4_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_sip4_mask_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_sip4_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_type_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
mlxsw_reg_rmft2_ipv4_pack(char *payload, bool v, u16 offset, u16 virtual_router,
			  enum mlxsw_reg_rmft2_irif_mask irif_mask, u16 irif,
			  u32 dip4, u32 dip4_mask, u32 sip4, u32 sip4_mask,
			  const char *flexible_action_set)
{
	mlxsw_reg_rmft2_common_pack(payload, v, offset, virtual_router,
				    irif_mask, irif, flexible_action_set);
	mlxsw_reg_rmft2_type_set(payload, MLXSW_REG_RMFT2_TYPE_IPV4);
	mlxsw_reg_rmft2_dip4_set(payload, dip4);
	mlxsw_reg_rmft2_dip4_mask_set(payload, dip4_mask);
	mlxsw_reg_rmft2_sip4_set(payload, sip4);
	mlxsw_reg_rmft2_sip4_mask_set(payload, sip4_mask);
}