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

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_rigr2_next_rigr_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rigr2_rigr_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rigr2_rmid_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rigr2_vnext_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_rigr2_vrmid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rigr2 ; 

__attribute__((used)) static inline void mlxsw_reg_rigr2_pack(char *payload, u32 rigr_index,
					bool vnext, u32 next_rigr_index)
{
	MLXSW_REG_ZERO(rigr2, payload);
	mlxsw_reg_rigr2_rigr_index_set(payload, rigr_index);
	mlxsw_reg_rigr2_vnext_set(payload, vnext);
	mlxsw_reg_rigr2_next_rigr_index_set(payload, next_rigr_index);
	mlxsw_reg_rigr2_vrmid_set(payload, 0);
	mlxsw_reg_rigr2_rmid_index_set(payload, 0);
}