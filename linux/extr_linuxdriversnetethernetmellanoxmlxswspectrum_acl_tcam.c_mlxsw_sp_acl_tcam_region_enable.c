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
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  tcam_region_info; int /*<<< orphan*/  id; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PACL_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_pacl_pack (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pacl ; 

__attribute__((used)) static int
mlxsw_sp_acl_tcam_region_enable(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_acl_tcam_region *region)
{
	char pacl_pl[MLXSW_REG_PACL_LEN];

	mlxsw_reg_pacl_pack(pacl_pl, region->id, true,
			    region->tcam_region_info);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(pacl), pacl_pl);
}