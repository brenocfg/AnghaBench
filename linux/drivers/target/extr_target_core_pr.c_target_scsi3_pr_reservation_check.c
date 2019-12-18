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
typedef  int /*<<< orphan*/  u32 ;
struct se_session {scalar_t__ se_node_acl; scalar_t__ sess_bin_isid; } ;
struct se_device {TYPE_1__* dev_pr_res_holder; } ;
struct se_cmd {int /*<<< orphan*/  pr_res_key; struct se_session* se_sess; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_2__ {scalar_t__ pr_reg_nacl; scalar_t__ pr_reg_bin_isid; scalar_t__ isid_present_at_reg; int /*<<< orphan*/  pr_res_key; int /*<<< orphan*/  pr_res_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCM_RESERVATION_CONFLICT ; 
 scalar_t__ core_scsi3_pr_seq_non_holder (struct se_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static sense_reason_t
target_scsi3_pr_reservation_check(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	struct se_session *sess = cmd->se_sess;
	u32 pr_reg_type;
	bool isid_mismatch = false;

	if (!dev->dev_pr_res_holder)
		return 0;

	pr_reg_type = dev->dev_pr_res_holder->pr_res_type;
	cmd->pr_res_key = dev->dev_pr_res_holder->pr_res_key;
	if (dev->dev_pr_res_holder->pr_reg_nacl != sess->se_node_acl)
		goto check_nonholder;

	if (dev->dev_pr_res_holder->isid_present_at_reg) {
		if (dev->dev_pr_res_holder->pr_reg_bin_isid !=
		    sess->sess_bin_isid) {
			isid_mismatch = true;
			goto check_nonholder;
		}
	}

	return 0;

check_nonholder:
	if (core_scsi3_pr_seq_non_holder(cmd, pr_reg_type, isid_mismatch))
		return TCM_RESERVATION_CONFLICT;
	return 0;
}