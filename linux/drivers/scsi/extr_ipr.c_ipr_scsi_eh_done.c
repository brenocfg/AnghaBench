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
struct ipr_hrr_queue {int /*<<< orphan*/  _lock; } ;
struct ipr_cmnd {struct ipr_hrr_queue* hrrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ipr_scsi_eh_done (struct ipr_cmnd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ipr_scsi_eh_done(struct ipr_cmnd *ipr_cmd)
{
	unsigned long hrrq_flags;
	struct ipr_hrr_queue *hrrq = ipr_cmd->hrrq;

	spin_lock_irqsave(&hrrq->_lock, hrrq_flags);
	__ipr_scsi_eh_done(ipr_cmd);
	spin_unlock_irqrestore(&hrrq->_lock, hrrq_flags);
}