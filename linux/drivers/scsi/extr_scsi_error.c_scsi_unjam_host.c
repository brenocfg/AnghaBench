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
struct Scsi_Host {int eh_deadline; int /*<<< orphan*/  host_lock; scalar_t__ last_reset; int /*<<< orphan*/  eh_cmd_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCSI_LOG_ERROR_RECOVERY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eh_done_q ; 
 int /*<<< orphan*/  eh_work_q ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_eh_flush_done_q (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_eh_get_sense (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_eh_prt_fail_stats (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_eh_ready_devs (struct Scsi_Host*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void scsi_unjam_host(struct Scsi_Host *shost)
{
	unsigned long flags;
	LIST_HEAD(eh_work_q);
	LIST_HEAD(eh_done_q);

	spin_lock_irqsave(shost->host_lock, flags);
	list_splice_init(&shost->eh_cmd_q, &eh_work_q);
	spin_unlock_irqrestore(shost->host_lock, flags);

	SCSI_LOG_ERROR_RECOVERY(1, scsi_eh_prt_fail_stats(shost, &eh_work_q));

	if (!scsi_eh_get_sense(&eh_work_q, &eh_done_q))
		scsi_eh_ready_devs(shost, &eh_work_q, &eh_done_q);

	spin_lock_irqsave(shost->host_lock, flags);
	if (shost->eh_deadline != -1)
		shost->last_reset = 0;
	spin_unlock_irqrestore(shost->host_lock, flags);
	scsi_eh_flush_done_q(&eh_done_q);
}