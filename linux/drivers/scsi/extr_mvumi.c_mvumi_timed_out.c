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
struct TYPE_8__ {int /*<<< orphan*/ * ptr; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  sc_data_direction; TYPE_3__ SCp; TYPE_1__* device; } ;
struct mvumi_hba {TYPE_5__* shost; TYPE_4__* pdev; int /*<<< orphan*/  fw_outstanding; int /*<<< orphan*/  tag_pool; int /*<<< orphan*/ ** tag_cmd; } ;
struct mvumi_cmd {int /*<<< orphan*/  queue_pointer; TYPE_2__* frame; } ;
struct Scsi_Host {int dummy; } ;
typedef  enum blk_eh_timer_return { ____Placeholder_blk_eh_timer_return } blk_eh_timer_return ;
struct TYPE_10__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {size_t tag; } ;
struct TYPE_6__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int BLK_EH_DONE ; 
 int DID_ABORT ; 
 int DRIVER_INVALID ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvumi_return_cmd (struct mvumi_hba*,struct mvumi_cmd*) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 struct mvumi_hba* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tag_release_one (struct mvumi_hba*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static enum blk_eh_timer_return mvumi_timed_out(struct scsi_cmnd *scmd)
{
	struct mvumi_cmd *cmd = (struct mvumi_cmd *) scmd->SCp.ptr;
	struct Scsi_Host *host = scmd->device->host;
	struct mvumi_hba *mhba = shost_priv(host);
	unsigned long flags;

	spin_lock_irqsave(mhba->shost->host_lock, flags);

	if (mhba->tag_cmd[cmd->frame->tag]) {
		mhba->tag_cmd[cmd->frame->tag] = NULL;
		tag_release_one(mhba, &mhba->tag_pool, cmd->frame->tag);
	}
	if (!list_empty(&cmd->queue_pointer))
		list_del_init(&cmd->queue_pointer);
	else
		atomic_dec(&mhba->fw_outstanding);

	scmd->result = (DRIVER_INVALID << 24) | (DID_ABORT << 16);
	scmd->SCp.ptr = NULL;
	if (scsi_bufflen(scmd)) {
		dma_unmap_sg(&mhba->pdev->dev, scsi_sglist(scmd),
			     scsi_sg_count(scmd),
			     scmd->sc_data_direction);
	}
	mvumi_return_cmd(mhba, cmd);
	spin_unlock_irqrestore(mhba->shost->host_lock, flags);

	return BLK_EH_DONE;
}