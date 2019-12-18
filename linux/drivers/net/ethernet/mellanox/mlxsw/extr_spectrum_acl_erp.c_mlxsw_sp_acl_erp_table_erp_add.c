#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/  erp_index_bitmap; int /*<<< orphan*/  base_index; TYPE_1__* aregion; TYPE_3__* erp_core; } ;
struct TYPE_5__ {int /*<<< orphan*/  mask; } ;
struct mlxsw_sp_acl_erp {int /*<<< orphan*/  index; TYPE_2__ key; int /*<<< orphan*/  id; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_reg_perpt_key_size { ____Placeholder_mlxsw_reg_perpt_key_size } mlxsw_reg_perpt_key_size ;
struct TYPE_6__ {struct mlxsw_sp* mlxsw_sp; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PERPT_LEN ; 
 int /*<<< orphan*/  MLXSW_SP_ACL_ERP_MAX_PER_REGION ; 
 int /*<<< orphan*/  mlxsw_reg_perpt_erp_vector_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_perpt_erp_vector_set (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_reg_perpt_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_table_locate (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perpt ; 

__attribute__((used)) static int
mlxsw_sp_acl_erp_table_erp_add(struct mlxsw_sp_acl_erp_table *erp_table,
			       struct mlxsw_sp_acl_erp *erp)
{
	struct mlxsw_sp *mlxsw_sp = erp_table->erp_core->mlxsw_sp;
	enum mlxsw_reg_perpt_key_size key_size;
	char perpt_pl[MLXSW_REG_PERPT_LEN];
	u8 erpt_bank, erpt_index;

	mlxsw_sp_acl_erp_table_locate(erp_table, erp, &erpt_bank, &erpt_index);
	key_size = (enum mlxsw_reg_perpt_key_size) erp_table->aregion->type;
	mlxsw_reg_perpt_pack(perpt_pl, erpt_bank, erpt_index, key_size, erp->id,
			     0, erp_table->base_index, erp->index,
			     erp->key.mask);
	mlxsw_reg_perpt_erp_vector_pack(perpt_pl, erp_table->erp_index_bitmap,
					MLXSW_SP_ACL_ERP_MAX_PER_REGION);
	mlxsw_reg_perpt_erp_vector_set(perpt_pl, erp->index, true);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(perpt), perpt_pl);
}