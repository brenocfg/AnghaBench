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
struct TYPE_2__ {int /*<<< orphan*/  dw; } ;
struct mlxsw_sp_acl {int /*<<< orphan*/  afk; int /*<<< orphan*/  ruleset_ht; int /*<<< orphan*/  dummy_fid; int /*<<< orphan*/  rules; int /*<<< orphan*/  tcam; TYPE_1__ rule_activity_update; } ;
struct mlxsw_sp {struct mlxsw_sp_acl* acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_afk_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_fini (struct mlxsw_sp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

void mlxsw_sp_acl_fini(struct mlxsw_sp *mlxsw_sp)
{
	struct mlxsw_sp_acl *acl = mlxsw_sp->acl;

	cancel_delayed_work_sync(&mlxsw_sp->acl->rule_activity_update.dw);
	mlxsw_sp_acl_tcam_fini(mlxsw_sp, &acl->tcam);
	WARN_ON(!list_empty(&acl->rules));
	mlxsw_sp_fid_put(acl->dummy_fid);
	rhashtable_destroy(&acl->ruleset_ht);
	mlxsw_afk_destroy(acl->afk);
	kfree(acl);
}