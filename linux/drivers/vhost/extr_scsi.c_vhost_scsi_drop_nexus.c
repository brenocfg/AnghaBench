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
struct vhost_scsi_tpg {scalar_t__ tv_tpg_port_count; scalar_t__ tv_tpg_vhost_count; int /*<<< orphan*/  tv_tpg_mutex; struct vhost_scsi_nexus* tpg_nexus; int /*<<< orphan*/  tport; } ;
struct vhost_scsi_nexus {struct se_session* tvn_se_sess; } ;
struct se_session {TYPE_1__* se_node_acl; } ;
struct TYPE_2__ {int /*<<< orphan*/  initiatorname; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  kfree (struct vhost_scsi_nexus*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  target_remove_session (struct se_session*) ; 
 int /*<<< orphan*/  vhost_scsi_dump_proto_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_scsi_free_cmd_map_res (struct se_session*) ; 

__attribute__((used)) static int vhost_scsi_drop_nexus(struct vhost_scsi_tpg *tpg)
{
	struct se_session *se_sess;
	struct vhost_scsi_nexus *tv_nexus;

	mutex_lock(&tpg->tv_tpg_mutex);
	tv_nexus = tpg->tpg_nexus;
	if (!tv_nexus) {
		mutex_unlock(&tpg->tv_tpg_mutex);
		return -ENODEV;
	}

	se_sess = tv_nexus->tvn_se_sess;
	if (!se_sess) {
		mutex_unlock(&tpg->tv_tpg_mutex);
		return -ENODEV;
	}

	if (tpg->tv_tpg_port_count != 0) {
		mutex_unlock(&tpg->tv_tpg_mutex);
		pr_err("Unable to remove TCM_vhost I_T Nexus with"
			" active TPG port count: %d\n",
			tpg->tv_tpg_port_count);
		return -EBUSY;
	}

	if (tpg->tv_tpg_vhost_count != 0) {
		mutex_unlock(&tpg->tv_tpg_mutex);
		pr_err("Unable to remove TCM_vhost I_T Nexus with"
			" active TPG vhost count: %d\n",
			tpg->tv_tpg_vhost_count);
		return -EBUSY;
	}

	pr_debug("TCM_vhost_ConfigFS: Removing I_T Nexus to emulated"
		" %s Initiator Port: %s\n", vhost_scsi_dump_proto_id(tpg->tport),
		tv_nexus->tvn_se_sess->se_node_acl->initiatorname);

	vhost_scsi_free_cmd_map_res(se_sess);
	/*
	 * Release the SCSI I_T Nexus to the emulated vhost Target Port
	 */
	target_remove_session(se_sess);
	tpg->tpg_nexus = NULL;
	mutex_unlock(&tpg->tv_tpg_mutex);

	kfree(tv_nexus);
	return 0;
}