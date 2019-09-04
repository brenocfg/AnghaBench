#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  id; } ;
struct mlxsw_sp_acl_erp_table {scalar_t__ num_ctcam_erps; int /*<<< orphan*/  erp_index_bitmap; int /*<<< orphan*/  base_index; TYPE_2__* erp_core; TYPE_1__* aregion; } ;
struct mlxsw_sp_acl_erp {int /*<<< orphan*/  index; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct TYPE_4__ {struct mlxsw_sp* mlxsw_sp; } ;
struct TYPE_3__ {struct mlxsw_sp_acl_tcam_region* region; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PERERP_LEN ; 
 int /*<<< orphan*/  MLXSW_SP_ACL_ERP_MAX_PER_REGION ; 
 int /*<<< orphan*/  mlxsw_reg_pererp_erp_vector_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pererp_erpt_vector_set (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_reg_pererp_pack (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pererp ; 

__attribute__((used)) static int
mlxsw_sp_acl_erp_region_erp_add(struct mlxsw_sp_acl_erp_table *erp_table,
				struct mlxsw_sp_acl_erp *erp)
{
	struct mlxsw_sp_acl_tcam_region *region = erp_table->aregion->region;
	struct mlxsw_sp *mlxsw_sp = erp_table->erp_core->mlxsw_sp;
	bool ctcam_le = erp_table->num_ctcam_erps > 0;
	char pererp_pl[MLXSW_REG_PERERP_LEN];

	mlxsw_reg_pererp_pack(pererp_pl, region->id, ctcam_le, true, 0,
			      erp_table->base_index, 0);
	mlxsw_reg_pererp_erp_vector_pack(pererp_pl, erp_table->erp_index_bitmap,
					 MLXSW_SP_ACL_ERP_MAX_PER_REGION);
	mlxsw_reg_pererp_erpt_vector_set(pererp_pl, erp->index, true);

	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(pererp), pererp_pl);
}