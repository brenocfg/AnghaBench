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
struct se_device {int /*<<< orphan*/  caw_sem; } ;
struct se_cmd {scalar_t__ scsi_status; int /*<<< orphan*/  t_state_lock; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 scalar_t__ SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int /*<<< orphan*/  TCM_NO_SENSE ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sense_reason_t compare_and_write_post(struct se_cmd *cmd, bool success,
					     int *post_ret)
{
	struct se_device *dev = cmd->se_dev;
	sense_reason_t ret = TCM_NO_SENSE;

	spin_lock_irq(&cmd->t_state_lock);
	if (success) {
		*post_ret = 1;

		if (cmd->scsi_status == SAM_STAT_CHECK_CONDITION)
			ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	}
	spin_unlock_irq(&cmd->t_state_lock);

	/*
	 * Unlock ->caw_sem originally obtained during sbc_compare_and_write()
	 * before the original READ I/O submission.
	 */
	up(&dev->caw_sem);

	return ret;
}