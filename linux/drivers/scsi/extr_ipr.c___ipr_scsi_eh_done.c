#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct ipr_cmnd {TYPE_1__* hrrq; int /*<<< orphan*/  queue; scalar_t__ eh_comp; struct scsi_cmnd* scsi_cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  hrrq_free_q; } ;

/* Variables and functions */
 int DID_ERROR ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void __ipr_scsi_eh_done(struct ipr_cmnd *ipr_cmd)
{
	struct scsi_cmnd *scsi_cmd = ipr_cmd->scsi_cmd;

	scsi_cmd->result |= (DID_ERROR << 16);

	scsi_dma_unmap(ipr_cmd->scsi_cmd);
	scsi_cmd->scsi_done(scsi_cmd);
	if (ipr_cmd->eh_comp)
		complete(ipr_cmd->eh_comp);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_free_q);
}