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
typedef  int /*<<< orphan*/  uint32_t ;
struct srb {int flags; TYPE_1__* cmd; scalar_t__ iocb_cnt; } ;
struct scsi_qla_host {int /*<<< orphan*/  iocb_cnt; int /*<<< orphan*/  host; } ;
struct scsi_cmnd {int dummy; } ;
struct TYPE_2__ {unsigned char* host_scribble; } ;

/* Variables and functions */
 scalar_t__ CMD_SP (struct scsi_cmnd*) ; 
 scalar_t__ MAX_SRBS ; 
 int SRB_DMA_VALID ; 
 struct scsi_cmnd* scsi_host_find_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct srb *qla4xxx_del_from_active_array(struct scsi_qla_host *ha,
    uint32_t index)
{
	struct srb *srb = NULL;
	struct scsi_cmnd *cmd = NULL;

	cmd = scsi_host_find_tag(ha->host, index);
	if (!cmd)
		return srb;

	srb = (struct srb *)CMD_SP(cmd);
	if (!srb)
		return srb;

	/* update counters */
	if (srb->flags & SRB_DMA_VALID) {
		ha->iocb_cnt -= srb->iocb_cnt;
		if (srb->cmd)
			srb->cmd->host_scribble =
				(unsigned char *)(unsigned long) MAX_SRBS;
	}
	return srb;
}