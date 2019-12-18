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
struct iscsi_tpg_np {int /*<<< orphan*/  tpg_np_kref; } ;
struct iscsi_tiqn {int dummy; } ;
struct iscsi_portal_group {int /*<<< orphan*/  np_login_sem; struct iscsi_tiqn* tpg_tiqn; } ;
struct iscsi_np {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsit_login_kref_put ; 
 int /*<<< orphan*/  iscsit_put_tiqn_for_login (struct iscsi_tiqn*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int iscsit_deaccess_np(struct iscsi_np *np, struct iscsi_portal_group *tpg,
		       struct iscsi_tpg_np *tpg_np)
{
	struct iscsi_tiqn *tiqn = tpg->tpg_tiqn;

	up(&tpg->np_login_sem);

	if (tpg_np)
		kref_put(&tpg_np->tpg_np_kref, iscsit_login_kref_put);

	if (tiqn)
		iscsit_put_tiqn_for_login(tiqn);

	return 0;
}