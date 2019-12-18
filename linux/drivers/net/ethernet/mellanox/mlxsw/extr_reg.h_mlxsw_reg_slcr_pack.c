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

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_SLCR_PP_GLOBAL ; 
 int /*<<< orphan*/  MLXSW_REG_SLCR_TYPE_CRC ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_slcr_lag_hash_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_slcr_pp_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_slcr_seed_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_slcr_type_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slcr ; 

__attribute__((used)) static inline void mlxsw_reg_slcr_pack(char *payload, u16 lag_hash, u32 seed)
{
	MLXSW_REG_ZERO(slcr, payload);
	mlxsw_reg_slcr_pp_set(payload, MLXSW_REG_SLCR_PP_GLOBAL);
	mlxsw_reg_slcr_type_set(payload, MLXSW_REG_SLCR_TYPE_CRC);
	mlxsw_reg_slcr_lag_hash_set(payload, lag_hash);
	mlxsw_reg_slcr_seed_set(payload, seed);
}