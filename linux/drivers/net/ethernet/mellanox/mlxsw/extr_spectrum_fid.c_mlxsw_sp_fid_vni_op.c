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
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SFMR_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_SFMR_OP_CREATE_FID ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfmr_nve_tunnel_flood_ptr_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfmr_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfmr_vni_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfmr_vtfp_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sfmr_vv_set (char*,int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sfmr ; 

__attribute__((used)) static int mlxsw_sp_fid_vni_op(struct mlxsw_sp *mlxsw_sp, u16 fid_index,
			       __be32 vni, bool vni_valid, u32 nve_flood_index,
			       bool nve_flood_index_valid)
{
	char sfmr_pl[MLXSW_REG_SFMR_LEN];

	mlxsw_reg_sfmr_pack(sfmr_pl, MLXSW_REG_SFMR_OP_CREATE_FID, fid_index,
			    0);
	mlxsw_reg_sfmr_vv_set(sfmr_pl, vni_valid);
	mlxsw_reg_sfmr_vni_set(sfmr_pl, be32_to_cpu(vni));
	mlxsw_reg_sfmr_vtfp_set(sfmr_pl, nve_flood_index_valid);
	mlxsw_reg_sfmr_nve_tunnel_flood_ptr_set(sfmr_pl, nve_flood_index);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sfmr), sfmr_pl);
}