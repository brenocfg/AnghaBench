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
typedef  enum mlxsw_reg_ptce2_op { ____Placeholder_mlxsw_reg_ptce2_op } mlxsw_reg_ptce2_op ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce2_offset_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce2_op_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce2_priority_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce2_tcam_region_info_memcpy_to (char*,char const*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce2_v_set (char*,int) ; 
 int /*<<< orphan*/  ptce2 ; 

__attribute__((used)) static inline void mlxsw_reg_ptce2_pack(char *payload, bool valid,
					enum mlxsw_reg_ptce2_op op,
					const char *tcam_region_info,
					u16 offset, u32 priority)
{
	MLXSW_REG_ZERO(ptce2, payload);
	mlxsw_reg_ptce2_v_set(payload, valid);
	mlxsw_reg_ptce2_op_set(payload, op);
	mlxsw_reg_ptce2_offset_set(payload, offset);
	mlxsw_reg_ptce2_priority_set(payload, priority);
	mlxsw_reg_ptce2_tcam_region_info_memcpy_to(payload, tcam_region_info);
}