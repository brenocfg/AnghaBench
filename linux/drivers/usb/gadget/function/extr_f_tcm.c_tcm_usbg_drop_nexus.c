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
struct usbg_tpg {int /*<<< orphan*/  tpg_mutex; struct tcm_usbg_nexus* tpg_nexus; int /*<<< orphan*/  tpg_port_count; } ;
struct tcm_usbg_nexus {struct se_session* tvn_se_sess; } ;
struct se_session {TYPE_1__* se_node_acl; } ;
struct TYPE_2__ {int /*<<< orphan*/  initiatorname; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  MSG ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tcm_usbg_nexus*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  target_remove_session (struct se_session*) ; 

__attribute__((used)) static int tcm_usbg_drop_nexus(struct usbg_tpg *tpg)
{
	struct se_session *se_sess;
	struct tcm_usbg_nexus *tv_nexus;
	int ret = -ENODEV;

	mutex_lock(&tpg->tpg_mutex);
	tv_nexus = tpg->tpg_nexus;
	if (!tv_nexus)
		goto out;

	se_sess = tv_nexus->tvn_se_sess;
	if (!se_sess)
		goto out;

	if (atomic_read(&tpg->tpg_port_count)) {
		ret = -EPERM;
#define MSG "Unable to remove Host I_T Nexus with active TPG port count: %d\n"
		pr_err(MSG, atomic_read(&tpg->tpg_port_count));
#undef MSG
		goto out;
	}

	pr_debug("Removing I_T Nexus to Initiator Port: %s\n",
			tv_nexus->tvn_se_sess->se_node_acl->initiatorname);
	/*
	 * Release the SCSI I_T Nexus to the emulated vHost Target Port
	 */
	target_remove_session(se_sess);
	tpg->tpg_nexus = NULL;

	kfree(tv_nexus);
	ret = 0;
out:
	mutex_unlock(&tpg->tpg_mutex);
	return ret;
}