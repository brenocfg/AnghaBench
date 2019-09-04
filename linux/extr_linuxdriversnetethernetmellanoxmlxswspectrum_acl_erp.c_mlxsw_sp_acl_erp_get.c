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
struct mlxsw_sp_acl_erp_table {TYPE_1__* ops; int /*<<< orphan*/  erp_ht; } ;
struct mlxsw_sp_acl_erp_key {int ctcam; int /*<<< orphan*/  mask; } ;
struct mlxsw_sp_acl_erp {int /*<<< orphan*/  refcnt; } ;
struct mlxsw_sp_acl_atcam_region {struct mlxsw_sp_acl_erp_table* erp_table; } ;
struct TYPE_2__ {struct mlxsw_sp_acl_erp* (* erp_create ) (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp_key*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_ht_params ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_acl_erp* rhashtable_lookup_fast (int /*<<< orphan*/ *,struct mlxsw_sp_acl_erp_key*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_acl_erp* stub1 (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp_key*) ; 

struct mlxsw_sp_acl_erp *
mlxsw_sp_acl_erp_get(struct mlxsw_sp_acl_atcam_region *aregion,
		     const char *mask, bool ctcam)
{
	struct mlxsw_sp_acl_erp_table *erp_table = aregion->erp_table;
	struct mlxsw_sp_acl_erp_key key;
	struct mlxsw_sp_acl_erp *erp;

	/* eRPs are allocated from a shared resource, but currently all
	 * allocations are done under RTNL.
	 */
	ASSERT_RTNL();

	memcpy(key.mask, mask, MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN);
	key.ctcam = ctcam;
	erp = rhashtable_lookup_fast(&erp_table->erp_ht, &key,
				     mlxsw_sp_acl_erp_ht_params);
	if (erp) {
		refcount_inc(&erp->refcnt);
		return erp;
	}

	return erp_table->ops->erp_create(erp_table, &key);
}