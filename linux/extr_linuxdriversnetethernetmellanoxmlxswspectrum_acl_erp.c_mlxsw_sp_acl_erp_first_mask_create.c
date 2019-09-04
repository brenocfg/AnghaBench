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
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/ * ops; } ;
struct mlxsw_sp_acl_erp_key {scalar_t__ ctcam; } ;
struct mlxsw_sp_acl_erp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mlxsw_sp_acl_erp* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  erp_single_mask_ops ; 
 struct mlxsw_sp_acl_erp* mlxsw_sp_acl_erp_generic_create (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp_key*) ; 

__attribute__((used)) static struct mlxsw_sp_acl_erp *
mlxsw_sp_acl_erp_first_mask_create(struct mlxsw_sp_acl_erp_table *erp_table,
				   struct mlxsw_sp_acl_erp_key *key)
{
	struct mlxsw_sp_acl_erp *erp;

	if (key->ctcam)
		return ERR_PTR(-EINVAL);

	erp = mlxsw_sp_acl_erp_generic_create(erp_table, key);
	if (IS_ERR(erp))
		return erp;

	erp_table->ops = &erp_single_mask_ops;

	return erp;
}