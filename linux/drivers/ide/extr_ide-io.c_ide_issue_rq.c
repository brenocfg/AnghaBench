#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct request {int rq_flags; int /*<<< orphan*/  queuelist; } ;
struct ide_host {int host_flags; TYPE_2__* cur_port; } ;
typedef  scalar_t__ ide_startstop_t ;
struct TYPE_14__ {int /*<<< orphan*/  lock; struct request* rq; TYPE_3__* cur_dev; struct ide_host* host; TYPE_1__* tp_ops; } ;
typedef  TYPE_2__ ide_hwif_t ;
struct TYPE_15__ {int dev_flags; int /*<<< orphan*/  rq_list; int /*<<< orphan*/  sleep; TYPE_2__* hwif; } ;
typedef  TYPE_3__ ide_drive_t ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_17__ {int /*<<< orphan*/ * special; } ;
struct TYPE_16__ {int /*<<< orphan*/  resid_len; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* write_devctl ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int ATA_DEVCTL_OBS ; 
 int ATA_NIEN ; 
 int /*<<< orphan*/  BLK_STS_DEV_RESOURCE ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int IDE_DFLAG_BLOCKED ; 
 int IDE_DFLAG_NIEN_QUIRK ; 
 int IDE_DFLAG_PARKED ; 
 int IDE_DFLAG_SLEEPING ; 
 int IDE_HFLAG_SERIALIZE ; 
 int RQF_DONTPREP ; 
 int RQF_PREEMPT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (struct request*) ; 
 scalar_t__ ata_pm_request (struct request*) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  blk_rq_is_passthrough (struct request*) ; 
 scalar_t__ ide_lock_host (struct ide_host*,TYPE_2__*) ; 
 int /*<<< orphan*/  ide_lock_port (TYPE_2__*) ; 
 TYPE_9__* ide_req (struct request*) ; 
 int /*<<< orphan*/  ide_requeue_and_plug (TYPE_3__*,struct request*) ; 
 scalar_t__ ide_stopped ; 
 int /*<<< orphan*/  ide_unlock_host (struct ide_host*) ; 
 int /*<<< orphan*/  ide_unlock_port (TYPE_2__*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 TYPE_6__* scsi_req (struct request*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ start_request (TYPE_3__*,struct request*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

blk_status_t ide_issue_rq(ide_drive_t *drive, struct request *rq,
			  bool local_requeue)
{
	ide_hwif_t *hwif = drive->hwif;
	struct ide_host *host = hwif->host;
	ide_startstop_t	startstop;

	if (!blk_rq_is_passthrough(rq) && !(rq->rq_flags & RQF_DONTPREP)) {
		rq->rq_flags |= RQF_DONTPREP;
		ide_req(rq)->special = NULL;
	}

	/* HLD do_request() callback might sleep, make sure it's okay */
	might_sleep();

	if (ide_lock_host(host, hwif))
		return BLK_STS_DEV_RESOURCE;

	spin_lock_irq(&hwif->lock);

	if (!ide_lock_port(hwif)) {
		ide_hwif_t *prev_port;

		WARN_ON_ONCE(hwif->rq);
repeat:
		prev_port = hwif->host->cur_port;
		if (drive->dev_flags & IDE_DFLAG_SLEEPING &&
		    time_after(drive->sleep, jiffies)) {
			ide_unlock_port(hwif);
			goto plug_device;
		}

		if ((hwif->host->host_flags & IDE_HFLAG_SERIALIZE) &&
		    hwif != prev_port) {
			ide_drive_t *cur_dev =
				prev_port ? prev_port->cur_dev : NULL;

			/*
			 * set nIEN for previous port, drives in the
			 * quirk list may not like intr setups/cleanups
			 */
			if (cur_dev &&
			    (cur_dev->dev_flags & IDE_DFLAG_NIEN_QUIRK) == 0)
				prev_port->tp_ops->write_devctl(prev_port,
								ATA_NIEN |
								ATA_DEVCTL_OBS);

			hwif->host->cur_port = hwif;
		}
		hwif->cur_dev = drive;
		drive->dev_flags &= ~(IDE_DFLAG_SLEEPING | IDE_DFLAG_PARKED);

		/*
		 * Sanity: don't accept a request that isn't a PM request
		 * if we are currently power managed. This is very important as
		 * blk_stop_queue() doesn't prevent the blk_fetch_request()
		 * above to return us whatever is in the queue. Since we call
		 * ide_do_request() ourselves, we end up taking requests while
		 * the queue is blocked...
		 * 
		 * We let requests forced at head of queue with ide-preempt
		 * though. I hope that doesn't happen too much, hopefully not
		 * unless the subdriver triggers such a thing in its own PM
		 * state machine.
		 */
		if ((drive->dev_flags & IDE_DFLAG_BLOCKED) &&
		    ata_pm_request(rq) == 0 &&
		    (rq->rq_flags & RQF_PREEMPT) == 0) {
			/* there should be no pending command at this point */
			ide_unlock_port(hwif);
			goto plug_device;
		}

		scsi_req(rq)->resid_len = blk_rq_bytes(rq);
		hwif->rq = rq;

		spin_unlock_irq(&hwif->lock);
		startstop = start_request(drive, rq);
		spin_lock_irq(&hwif->lock);

		if (startstop == ide_stopped) {
			rq = hwif->rq;
			hwif->rq = NULL;
			if (rq)
				goto repeat;
			ide_unlock_port(hwif);
			goto out;
		}
	} else {
plug_device:
		if (local_requeue)
			list_add(&rq->queuelist, &drive->rq_list);
		spin_unlock_irq(&hwif->lock);
		ide_unlock_host(host);
		if (!local_requeue)
			ide_requeue_and_plug(drive, rq);
		return BLK_STS_OK;
	}

out:
	spin_unlock_irq(&hwif->lock);
	if (rq == NULL)
		ide_unlock_host(host);
	return BLK_STS_OK;
}