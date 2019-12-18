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
struct iscsi_host {scalar_t__ num_sessions; scalar_t__ workq; int /*<<< orphan*/  session_removal_wq; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_HOST_REMOVED ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_host_for_each_session (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_notify_host_removed ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 struct iscsi_host* shost_priv (struct Scsi_Host*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

void iscsi_host_remove(struct Scsi_Host *shost)
{
	struct iscsi_host *ihost = shost_priv(shost);
	unsigned long flags;

	spin_lock_irqsave(&ihost->lock, flags);
	ihost->state = ISCSI_HOST_REMOVED;
	spin_unlock_irqrestore(&ihost->lock, flags);

	iscsi_host_for_each_session(shost, iscsi_notify_host_removed);
	wait_event_interruptible(ihost->session_removal_wq,
				 ihost->num_sessions == 0);
	if (signal_pending(current))
		flush_signals(current);

	scsi_remove_host(shost);
	if (ihost->workq)
		destroy_workqueue(ihost->workq);
}