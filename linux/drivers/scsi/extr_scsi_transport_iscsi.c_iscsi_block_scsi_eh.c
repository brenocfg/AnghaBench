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
struct scsi_cmnd {int /*<<< orphan*/  device; } ;
struct iscsi_cls_session {scalar_t__ state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int FAST_IO_FAIL ; 
 scalar_t__ ISCSI_SESSION_FREE ; 
 scalar_t__ ISCSI_SESSION_LOGGED_IN ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  scsi_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct iscsi_cls_session* starget_to_session (int /*<<< orphan*/ ) ; 

int iscsi_block_scsi_eh(struct scsi_cmnd *cmd)
{
	struct iscsi_cls_session *session =
			starget_to_session(scsi_target(cmd->device));
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&session->lock, flags);
	while (session->state != ISCSI_SESSION_LOGGED_IN) {
		if (session->state == ISCSI_SESSION_FREE) {
			ret = FAST_IO_FAIL;
			break;
		}
		spin_unlock_irqrestore(&session->lock, flags);
		msleep(1000);
		spin_lock_irqsave(&session->lock, flags);
	}
	spin_unlock_irqrestore(&session->lock, flags);
	return ret;
}