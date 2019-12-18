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
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;
typedef  enum mlxsw_reg_sbpr_mode { ____Placeholder_mlxsw_reg_sbpr_mode } mlxsw_reg_sbpr_mode ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_sbpr_dir_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sbpr_infi_size_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sbpr_mode_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sbpr_pool_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sbpr_size_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbpr ; 

__attribute__((used)) static inline void mlxsw_reg_sbpr_pack(char *payload, u8 pool,
				       enum mlxsw_reg_sbxx_dir dir,
				       enum mlxsw_reg_sbpr_mode mode, u32 size,
				       bool infi_size)
{
	MLXSW_REG_ZERO(sbpr, payload);
	mlxsw_reg_sbpr_pool_set(payload, pool);
	mlxsw_reg_sbpr_dir_set(payload, dir);
	mlxsw_reg_sbpr_mode_set(payload, mode);
	mlxsw_reg_sbpr_size_set(payload, size);
	mlxsw_reg_sbpr_infi_size_set(payload, infi_size);
}