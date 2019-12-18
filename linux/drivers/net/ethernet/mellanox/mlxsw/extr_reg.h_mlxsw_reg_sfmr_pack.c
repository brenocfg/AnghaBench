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
typedef  enum mlxsw_reg_sfmr_op { ____Placeholder_mlxsw_reg_sfmr_op } mlxsw_reg_sfmr_op ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_sfmr_fid_offset_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfmr_fid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfmr_op_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sfmr_vtfp_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sfmr_vv_set (char*,int) ; 
 int /*<<< orphan*/  sfmr ; 

__attribute__((used)) static inline void mlxsw_reg_sfmr_pack(char *payload,
				       enum mlxsw_reg_sfmr_op op, u16 fid,
				       u16 fid_offset)
{
	MLXSW_REG_ZERO(sfmr, payload);
	mlxsw_reg_sfmr_op_set(payload, op);
	mlxsw_reg_sfmr_fid_set(payload, fid);
	mlxsw_reg_sfmr_fid_offset_set(payload, fid_offset);
	mlxsw_reg_sfmr_vtfp_set(payload, false);
	mlxsw_reg_sfmr_vv_set(payload, false);
}