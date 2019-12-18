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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlxsw_reg_ptce3_op { ____Placeholder_mlxsw_reg_ptce3_op } mlxsw_reg_ptce3_op ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce3_action_pointer_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce3_delta_mask_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce3_delta_start_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce3_delta_value_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce3_erp_id_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce3_flex2_key_blocks_memcpy_to (char*,char const*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce3_large_entry_key_id_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce3_large_exists_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce3_op_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce3_priority_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce3_tcam_region_info_memcpy_to (char*,char const*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce3_v_set (char*,int) ; 
 int /*<<< orphan*/  ptce3 ; 

__attribute__((used)) static inline void mlxsw_reg_ptce3_pack(char *payload, bool valid,
					enum mlxsw_reg_ptce3_op op,
					u32 priority,
					const char *tcam_region_info,
					const char *key, u8 erp_id,
					u16 delta_start, u8 delta_mask,
					u8 delta_value, bool large_exists,
					u32 lkey_id, u32 action_pointer)
{
	MLXSW_REG_ZERO(ptce3, payload);
	mlxsw_reg_ptce3_v_set(payload, valid);
	mlxsw_reg_ptce3_op_set(payload, op);
	mlxsw_reg_ptce3_priority_set(payload, priority);
	mlxsw_reg_ptce3_tcam_region_info_memcpy_to(payload, tcam_region_info);
	mlxsw_reg_ptce3_flex2_key_blocks_memcpy_to(payload, key);
	mlxsw_reg_ptce3_erp_id_set(payload, erp_id);
	mlxsw_reg_ptce3_delta_start_set(payload, delta_start);
	mlxsw_reg_ptce3_delta_mask_set(payload, delta_mask);
	mlxsw_reg_ptce3_delta_value_set(payload, delta_value);
	mlxsw_reg_ptce3_large_exists_set(payload, large_exists);
	mlxsw_reg_ptce3_large_entry_key_id_set(payload, lkey_id);
	mlxsw_reg_ptce3_action_pointer_set(payload, action_pointer);
}