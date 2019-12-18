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
struct mlxsw_sp_acl_erp_table {scalar_t__ num_ctcam_erps; scalar_t__ num_deltas; int num_atcam_erps; int /*<<< orphan*/ * ops; int /*<<< orphan*/  base_index; TYPE_1__* aregion; int /*<<< orphan*/  num_max_atcam_erps; int /*<<< orphan*/  erp_core; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  erp_no_mask_ops ; 
 int /*<<< orphan*/  erp_single_mask_ops ; 
 int /*<<< orphan*/  erp_two_masks_ops ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_region_master_mask_trans (struct mlxsw_sp_acl_erp_table*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_table_disable (struct mlxsw_sp_acl_erp_table*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_table_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__mlxsw_sp_acl_erp_table_other_dec(struct mlxsw_sp_acl_erp_table *erp_table,
				   unsigned int *dec_num)
{
	(*dec_num)--;

	/* If there are no C-TCAM eRP or deltas in use, the state we
	 * transition to depends on the number of A-TCAM eRPs currently
	 * in use.
	 */
	if (erp_table->num_ctcam_erps > 0 || erp_table->num_deltas > 0)
		return;

	switch (erp_table->num_atcam_erps) {
	case 2:
		/* Keep using the eRP table, but correctly set the
		 * operations pointer so that when an A-TCAM eRP is
		 * deleted we will transition to use the master mask
		 */
		erp_table->ops = &erp_two_masks_ops;
		break;
	case 1:
		/* We only kept the eRP table because we had C-TCAM
		 * eRPs in use. Now that the last C-TCAM eRP is gone we
		 * can stop using the table and transition to use the
		 * master mask
		 */
		mlxsw_sp_acl_erp_region_master_mask_trans(erp_table);
		erp_table->ops = &erp_single_mask_ops;
		break;
	case 0:
		/* There are no more eRPs of any kind used by the region
		 * so free its eRP table and transition to initial state
		 */
		mlxsw_sp_acl_erp_table_disable(erp_table);
		mlxsw_sp_acl_erp_table_free(erp_table->erp_core,
					    erp_table->num_max_atcam_erps,
					    erp_table->aregion->type,
					    erp_table->base_index);
		erp_table->ops = &erp_no_mask_ops;
		break;
	default:
		break;
	}
}