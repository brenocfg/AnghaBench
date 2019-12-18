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
typedef  enum mlxsw_reg_perpt_key_size { ____Placeholder_mlxsw_reg_perpt_key_size } mlxsw_reg_perpt_key_size ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_perpt_bf_bypass_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_perpt_erp_id_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_perpt_erp_index_in_vector_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_perpt_erpt_bank_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_perpt_erpt_base_bank_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_perpt_erpt_base_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_perpt_erpt_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_perpt_key_size_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_perpt_mask_memcpy_to (char*,char*) ; 
 int /*<<< orphan*/  perpt ; 

__attribute__((used)) static inline void
mlxsw_reg_perpt_pack(char *payload, u8 erpt_bank, u8 erpt_index,
		     enum mlxsw_reg_perpt_key_size key_size, u8 erp_id,
		     u8 erpt_base_bank, u8 erpt_base_index, u8 erp_index,
		     char *mask)
{
	MLXSW_REG_ZERO(perpt, payload);
	mlxsw_reg_perpt_erpt_bank_set(payload, erpt_bank);
	mlxsw_reg_perpt_erpt_index_set(payload, erpt_index);
	mlxsw_reg_perpt_key_size_set(payload, key_size);
	mlxsw_reg_perpt_bf_bypass_set(payload, false);
	mlxsw_reg_perpt_erp_id_set(payload, erp_id);
	mlxsw_reg_perpt_erpt_base_bank_set(payload, erpt_base_bank);
	mlxsw_reg_perpt_erpt_base_index_set(payload, erpt_base_index);
	mlxsw_reg_perpt_erp_index_in_vector_set(payload, erp_index);
	mlxsw_reg_perpt_mask_memcpy_to(payload, mask);
}