#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct se_session {int dummy; } ;
struct se_portal_group {int dummy; } ;
struct se_node_acl {int dummy; } ;
struct TYPE_6__ {struct TYPE_6__* se_node_acl; struct TYPE_6__* se_tpg; struct TYPE_6__* nacl_sess; int /*<<< orphan*/  acl_sess_list; int /*<<< orphan*/  acl_list; int /*<<< orphan*/ * se_tpg_tfo; int /*<<< orphan*/  tpg_sess_list; int /*<<< orphan*/  acl_node_list; int /*<<< orphan*/  se_tpg_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int transport_init_session (TYPE_1__*) ; 
 TYPE_1__ xcopy_pt_nacl ; 
 TYPE_1__ xcopy_pt_sess ; 
 int /*<<< orphan*/  xcopy_pt_tfo ; 
 TYPE_1__ xcopy_pt_tpg ; 
 int /*<<< orphan*/  xcopy_wq ; 

int target_xcopy_setup_pt(void)
{
	int ret;

	xcopy_wq = alloc_workqueue("xcopy_wq", WQ_MEM_RECLAIM, 0);
	if (!xcopy_wq) {
		pr_err("Unable to allocate xcopy_wq\n");
		return -ENOMEM;
	}

	memset(&xcopy_pt_tpg, 0, sizeof(struct se_portal_group));
	INIT_LIST_HEAD(&xcopy_pt_tpg.se_tpg_node);
	INIT_LIST_HEAD(&xcopy_pt_tpg.acl_node_list);
	INIT_LIST_HEAD(&xcopy_pt_tpg.tpg_sess_list);

	xcopy_pt_tpg.se_tpg_tfo = &xcopy_pt_tfo;

	memset(&xcopy_pt_nacl, 0, sizeof(struct se_node_acl));
	INIT_LIST_HEAD(&xcopy_pt_nacl.acl_list);
	INIT_LIST_HEAD(&xcopy_pt_nacl.acl_sess_list);
	memset(&xcopy_pt_sess, 0, sizeof(struct se_session));
	ret = transport_init_session(&xcopy_pt_sess);
	if (ret < 0)
		return ret;

	xcopy_pt_nacl.se_tpg = &xcopy_pt_tpg;
	xcopy_pt_nacl.nacl_sess = &xcopy_pt_sess;

	xcopy_pt_sess.se_tpg = &xcopy_pt_tpg;
	xcopy_pt_sess.se_node_acl = &xcopy_pt_nacl;

	return 0;
}