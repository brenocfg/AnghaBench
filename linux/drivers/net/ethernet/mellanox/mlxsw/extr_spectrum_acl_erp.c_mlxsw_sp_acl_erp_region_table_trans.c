#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/  base_index; TYPE_1__* aregion; int /*<<< orphan*/  num_max_atcam_erps; int /*<<< orphan*/  erp_index_bitmap; struct mlxsw_sp_acl_erp_core* erp_core; } ;
struct mlxsw_sp_acl_erp_core {int /*<<< orphan*/  num_erp_banks; } ;
struct mlxsw_sp_acl_erp {scalar_t__ index; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int mlxsw_acl_erp_table_bf_add (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  mlxsw_acl_erp_table_bf_del (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp*) ; 
 int mlxsw_sp_acl_erp_table_alloc (struct mlxsw_sp_acl_erp_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_acl_erp_table_enable (struct mlxsw_sp_acl_erp_table*,int) ; 
 int mlxsw_sp_acl_erp_table_erp_add (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_table_erp_del (struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_table_free (struct mlxsw_sp_acl_erp_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_acl_erp* mlxsw_sp_acl_erp_table_master_rp (struct mlxsw_sp_acl_erp_table*) ; 

__attribute__((used)) static int
mlxsw_sp_acl_erp_region_table_trans(struct mlxsw_sp_acl_erp_table *erp_table)
{
	struct mlxsw_sp_acl_erp_core *erp_core = erp_table->erp_core;
	struct mlxsw_sp_acl_erp *master_rp;
	int err;

	/* Initially, allocate a single eRP row. Expand later as needed */
	err = mlxsw_sp_acl_erp_table_alloc(erp_core, erp_core->num_erp_banks,
					   erp_table->aregion->type,
					   &erp_table->base_index);
	if (err)
		return err;
	erp_table->num_max_atcam_erps = erp_core->num_erp_banks;

	/* Transition the sole RP currently configured (the master RP)
	 * to the eRP table
	 */
	master_rp = mlxsw_sp_acl_erp_table_master_rp(erp_table);
	if (!master_rp) {
		err = -EINVAL;
		goto err_table_master_rp;
	}

	/* Make sure the master RP is using a valid index, as
	 * only a single eRP row is currently allocated.
	 */
	master_rp->index = 0;
	__set_bit(master_rp->index, erp_table->erp_index_bitmap);

	err = mlxsw_sp_acl_erp_table_erp_add(erp_table, master_rp);
	if (err)
		goto err_table_master_rp_add;

	/* Update Bloom filter before enabling eRP table, as rules
	 * on the master RP were not set to Bloom filter up to this
	 * point.
	 */
	err = mlxsw_acl_erp_table_bf_add(erp_table, master_rp);
	if (err)
		goto err_table_bf_add;

	err = mlxsw_sp_acl_erp_table_enable(erp_table, false);
	if (err)
		goto err_table_enable;

	return 0;

err_table_enable:
	mlxsw_acl_erp_table_bf_del(erp_table, master_rp);
err_table_bf_add:
	mlxsw_sp_acl_erp_table_erp_del(master_rp);
err_table_master_rp_add:
	__clear_bit(master_rp->index, erp_table->erp_index_bitmap);
err_table_master_rp:
	mlxsw_sp_acl_erp_table_free(erp_core, erp_table->num_max_atcam_erps,
				    erp_table->aregion->type,
				    erp_table->base_index);
	return err;
}