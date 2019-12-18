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
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  tcam_region_info; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PTCE2_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_PTCE2_OP_QUERY_CLEAR_ON_READ ; 
 int mlxsw_reg_ptce2_a_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce2_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ptce2 ; 

__attribute__((used)) static int
mlxsw_sp1_acl_tcam_region_entry_activity_get(struct mlxsw_sp *mlxsw_sp,
					     struct mlxsw_sp_acl_tcam_region *_region,
					     unsigned int offset,
					     bool *activity)
{
	char ptce2_pl[MLXSW_REG_PTCE2_LEN];
	int err;

	mlxsw_reg_ptce2_pack(ptce2_pl, true, MLXSW_REG_PTCE2_OP_QUERY_CLEAR_ON_READ,
			     _region->tcam_region_info, offset, 0);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ptce2), ptce2_pl);
	if (err)
		return err;
	*activity = mlxsw_reg_ptce2_a_get(ptce2_pl);
	return 0;
}