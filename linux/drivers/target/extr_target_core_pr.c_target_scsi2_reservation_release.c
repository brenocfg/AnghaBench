#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct se_session {scalar_t__ sess_bin_isid; TYPE_4__* se_node_acl; struct se_portal_group* se_tpg; } ;
struct se_portal_group {TYPE_2__* se_tpg_tfo; } ;
struct se_device {scalar_t__ dev_res_bin_isid; int /*<<< orphan*/  dev_reservation_lock; TYPE_1__* reservation_holder; } ;
struct se_cmd {int /*<<< orphan*/  orig_fe_lun; TYPE_3__* se_lun; struct se_session* se_sess; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_8__ {int /*<<< orphan*/  initiatorname; } ;
struct TYPE_7__ {int /*<<< orphan*/  unpacked_lun; } ;
struct TYPE_6__ {int /*<<< orphan*/  fabric_name; } ;
struct TYPE_5__ {TYPE_4__* se_node_acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOOD ; 
 int /*<<< orphan*/  TCM_RESERVATION_CONFLICT ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int target_check_scsi2_reservation_conflict (struct se_cmd*) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_release_reservation (struct se_device*) ; 

sense_reason_t
target_scsi2_reservation_release(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	struct se_session *sess = cmd->se_sess;
	struct se_portal_group *tpg;
	int rc;

	if (!sess || !sess->se_tpg)
		goto out;
	rc = target_check_scsi2_reservation_conflict(cmd);
	if (rc == 1)
		goto out;
	if (rc < 0)
		return TCM_RESERVATION_CONFLICT;

	spin_lock(&dev->dev_reservation_lock);
	if (!dev->reservation_holder || !sess)
		goto out_unlock;

	if (dev->reservation_holder->se_node_acl != sess->se_node_acl)
		goto out_unlock;

	if (dev->dev_res_bin_isid != sess->sess_bin_isid)
		goto out_unlock;

	target_release_reservation(dev);
	tpg = sess->se_tpg;
	pr_debug("SCSI-2 Released reservation for %s LUN: %llu ->"
		" MAPPED LUN: %llu for %s\n",
		tpg->se_tpg_tfo->fabric_name,
		cmd->se_lun->unpacked_lun, cmd->orig_fe_lun,
		sess->se_node_acl->initiatorname);

out_unlock:
	spin_unlock(&dev->dev_reservation_lock);
out:
	target_complete_cmd(cmd, GOOD);
	return 0;
}