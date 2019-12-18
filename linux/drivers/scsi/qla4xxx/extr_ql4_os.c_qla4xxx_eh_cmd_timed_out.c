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
struct iscsi_session {int dummy; } ;
struct iscsi_cls_session {scalar_t__ state; int /*<<< orphan*/  lock; struct iscsi_session* dd_data; } ;
typedef  enum blk_eh_timer_return { ____Placeholder_blk_eh_timer_return } blk_eh_timer_return ;

/* Variables and functions */
 int BLK_EH_DONE ; 
 int BLK_EH_RESET_TIMER ; 
 scalar_t__ ISCSI_SESSION_FAILED ; 
 int /*<<< orphan*/  scsi_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct iscsi_cls_session* starget_to_session (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum blk_eh_timer_return qla4xxx_eh_cmd_timed_out(struct scsi_cmnd *sc)
{
	struct iscsi_cls_session *session;
	struct iscsi_session *sess;
	unsigned long flags;
	enum blk_eh_timer_return ret = BLK_EH_DONE;

	session = starget_to_session(scsi_target(sc->device));
	sess = session->dd_data;

	spin_lock_irqsave(&session->lock, flags);
	if (session->state == ISCSI_SESSION_FAILED)
		ret = BLK_EH_RESET_TIMER;
	spin_unlock_irqrestore(&session->lock, flags);

	return ret;
}