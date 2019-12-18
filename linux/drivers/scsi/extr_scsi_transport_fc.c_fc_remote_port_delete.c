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
struct fc_rport {unsigned long dev_loss_tmo; scalar_t__ port_state; int fast_io_fail_tmo; int /*<<< orphan*/  dev_loss_work; int /*<<< orphan*/  fail_io_work; int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 scalar_t__ FC_PORTSTATE_BLOCKED ; 
 scalar_t__ FC_PORTSTATE_ONLINE ; 
 int /*<<< orphan*/  FC_RPORT_DEVLOSS_PENDING ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  fc_queue_devloss_work (struct Scsi_Host*,int /*<<< orphan*/ *,unsigned long) ; 
 struct Scsi_Host* rport_to_shost (struct fc_rport*) ; 
 int /*<<< orphan*/  scsi_target_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void
fc_remote_port_delete(struct fc_rport  *rport)
{
	struct Scsi_Host *shost = rport_to_shost(rport);
	unsigned long timeout = rport->dev_loss_tmo;
	unsigned long flags;

	/*
	 * No need to flush the fc_host work_q's, as all adds are synchronous.
	 *
	 * We do need to reclaim the rport scan work element, so eventually
	 * (in fc_rport_final_delete()) we'll flush the scsi host work_q if
	 * there's still a scan pending.
	 */

	spin_lock_irqsave(shost->host_lock, flags);

	if (rport->port_state != FC_PORTSTATE_ONLINE) {
		spin_unlock_irqrestore(shost->host_lock, flags);
		return;
	}

	/*
	 * In the past, we if this was not an FCP-Target, we would
	 * unconditionally just jump to deleting the rport.
	 * However, rports can be used as node containers by the LLDD,
	 * and its not appropriate to just terminate the rport at the
	 * first sign of a loss in connectivity. The LLDD may want to
	 * send ELS traffic to re-validate the login. If the rport is
	 * immediately deleted, it makes it inappropriate for a node
	 * container.
	 * So... we now unconditionally wait dev_loss_tmo before
	 * destroying an rport.
	 */

	rport->port_state = FC_PORTSTATE_BLOCKED;

	rport->flags |= FC_RPORT_DEVLOSS_PENDING;

	spin_unlock_irqrestore(shost->host_lock, flags);

	scsi_target_block(&rport->dev);

	/* see if we need to kill io faster than waiting for device loss */
	if ((rport->fast_io_fail_tmo != -1) &&
	    (rport->fast_io_fail_tmo < timeout))
		fc_queue_devloss_work(shost, &rport->fail_io_work,
					rport->fast_io_fail_tmo * HZ);

	/* cap the length the devices can be blocked until they are deleted */
	fc_queue_devloss_work(shost, &rport->dev_loss_work, timeout * HZ);
}