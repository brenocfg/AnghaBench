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
struct iscsi_tpg_np {int /*<<< orphan*/ * tpg; int /*<<< orphan*/ * tpg_np; } ;
struct iscsi_portal_group {int /*<<< orphan*/  tpgt; TYPE_1__* tpg_tiqn; } ;
struct iscsi_np {TYPE_2__* np_transport; int /*<<< orphan*/  np_sockaddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  tiqn; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsit_clear_tpg_np_login_thread (struct iscsi_tpg_np*,struct iscsi_portal_group*,int) ; 
 int iscsit_del_np (struct iscsi_np*) ; 
 int /*<<< orphan*/  kfree (struct iscsi_tpg_np*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsit_tpg_release_np(
	struct iscsi_tpg_np *tpg_np,
	struct iscsi_portal_group *tpg,
	struct iscsi_np *np)
{
	iscsit_clear_tpg_np_login_thread(tpg_np, tpg, true);

	pr_debug("CORE[%s] - Removed Network Portal: %pISpc,%hu on %s\n",
		tpg->tpg_tiqn->tiqn, &np->np_sockaddr, tpg->tpgt,
		np->np_transport->name);

	tpg_np->tpg_np = NULL;
	tpg_np->tpg = NULL;
	kfree(tpg_np);
	/*
	 * iscsit_del_np() will shutdown struct iscsi_np when last TPG reference is released.
	 */
	return iscsit_del_np(np);
}