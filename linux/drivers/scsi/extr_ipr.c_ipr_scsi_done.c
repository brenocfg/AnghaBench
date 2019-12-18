#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct ipr_ioa_cfg {TYPE_5__* host; } ;
struct TYPE_6__ {int /*<<< orphan*/  residual_data_len; int /*<<< orphan*/  ioasc; } ;
struct TYPE_7__ {TYPE_1__ hdr; } ;
struct TYPE_8__ {TYPE_2__ ioasa; } ;
struct ipr_cmnd {TYPE_4__* hrrq; int /*<<< orphan*/  queue; scalar_t__ eh_comp; TYPE_3__ s; struct scsi_cmnd* scsi_cmd; struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_10__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  _lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  hrrq_free_q; } ;

/* Variables and functions */
 scalar_t__ IPR_IOASC_SENSE_KEY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  ipr_erp_start (struct ipr_ioa_cfg*,struct ipr_cmnd*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void ipr_scsi_done(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	struct scsi_cmnd *scsi_cmd = ipr_cmd->scsi_cmd;
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);
	unsigned long lock_flags;

	scsi_set_resid(scsi_cmd, be32_to_cpu(ipr_cmd->s.ioasa.hdr.residual_data_len));

	if (likely(IPR_IOASC_SENSE_KEY(ioasc) == 0)) {
		scsi_dma_unmap(scsi_cmd);

		spin_lock_irqsave(ipr_cmd->hrrq->lock, lock_flags);
		scsi_cmd->scsi_done(scsi_cmd);
		if (ipr_cmd->eh_comp)
			complete(ipr_cmd->eh_comp);
		list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_free_q);
		spin_unlock_irqrestore(ipr_cmd->hrrq->lock, lock_flags);
	} else {
		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
		spin_lock(&ipr_cmd->hrrq->_lock);
		ipr_erp_start(ioa_cfg, ipr_cmd);
		spin_unlock(&ipr_cmd->hrrq->_lock);
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	}
}