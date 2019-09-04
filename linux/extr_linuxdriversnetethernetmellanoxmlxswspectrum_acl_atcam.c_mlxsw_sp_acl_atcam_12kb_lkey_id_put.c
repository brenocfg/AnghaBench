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
struct mlxsw_sp_acl_atcam_region {int dummy; } ;
struct mlxsw_sp_acl_atcam_lkey_id {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_atcam_lkey_id_destroy (struct mlxsw_sp_acl_atcam_region*,struct mlxsw_sp_acl_atcam_lkey_id*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_acl_atcam_12kb_lkey_id_put(struct mlxsw_sp_acl_atcam_region *aregion,
				    struct mlxsw_sp_acl_atcam_lkey_id *lkey_id)
{
	if (refcount_dec_and_test(&lkey_id->refcnt))
		mlxsw_sp_acl_atcam_lkey_id_destroy(aregion, lkey_id);
}