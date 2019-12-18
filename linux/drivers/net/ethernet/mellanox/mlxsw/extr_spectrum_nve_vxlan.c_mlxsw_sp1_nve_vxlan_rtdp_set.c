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
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RTDP_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_RTDP_TYPE_NVE ; 
 int /*<<< orphan*/  mlxsw_reg_rtdp_pack (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtdp ; 

__attribute__((used)) static int mlxsw_sp1_nve_vxlan_rtdp_set(struct mlxsw_sp *mlxsw_sp,
					unsigned int tunnel_index)
{
	char rtdp_pl[MLXSW_REG_RTDP_LEN];

	mlxsw_reg_rtdp_pack(rtdp_pl, MLXSW_REG_RTDP_TYPE_NVE, tunnel_index);

	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(rtdp), rtdp_pl);
}