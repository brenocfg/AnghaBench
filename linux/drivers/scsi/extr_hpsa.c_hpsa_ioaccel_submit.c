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
struct scsi_cmnd {unsigned char* host_scribble; TYPE_1__* device; } ;
struct hpsa_scsi_dev_t {scalar_t__ hba_ioaccel_enabled; scalar_t__ offload_enabled; scalar_t__ in_reset; } ;
struct ctlr_info {int dummy; } ;
struct CommandList {struct hpsa_scsi_dev_t* device; struct scsi_cmnd* scsi_cmd; void* cmd_type; int /*<<< orphan*/  cmdindex; } ;
struct TYPE_2__ {struct hpsa_scsi_dev_t* hostdata; } ;

/* Variables and functions */
 void* CMD_SCSI ; 
 int IO_ACCEL_INELIGIBLE ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int /*<<< orphan*/  hpsa_cmd_init (struct ctlr_info*,int /*<<< orphan*/ ,struct CommandList*) ; 
 int hpsa_scsi_ioaccel_direct_map (struct ctlr_info*,struct CommandList*) ; 
 int hpsa_scsi_ioaccel_raid_map (struct ctlr_info*,struct CommandList*) ; 
 scalar_t__ hpsa_simple_mode ; 

__attribute__((used)) static int hpsa_ioaccel_submit(struct ctlr_info *h,
		struct CommandList *c, struct scsi_cmnd *cmd)
{
	struct hpsa_scsi_dev_t *dev = cmd->device->hostdata;
	int rc = IO_ACCEL_INELIGIBLE;

	if (!dev)
		return SCSI_MLQUEUE_HOST_BUSY;

	if (dev->in_reset)
		return SCSI_MLQUEUE_HOST_BUSY;

	if (hpsa_simple_mode)
		return IO_ACCEL_INELIGIBLE;

	cmd->host_scribble = (unsigned char *) c;

	if (dev->offload_enabled) {
		hpsa_cmd_init(h, c->cmdindex, c);
		c->cmd_type = CMD_SCSI;
		c->scsi_cmd = cmd;
		c->device = dev;
		rc = hpsa_scsi_ioaccel_raid_map(h, c);
		if (rc < 0)     /* scsi_dma_map failed. */
			rc = SCSI_MLQUEUE_HOST_BUSY;
	} else if (dev->hba_ioaccel_enabled) {
		hpsa_cmd_init(h, c->cmdindex, c);
		c->cmd_type = CMD_SCSI;
		c->scsi_cmd = cmd;
		c->device = dev;
		rc = hpsa_scsi_ioaccel_direct_map(h, c);
		if (rc < 0)     /* scsi_dma_map failed. */
			rc = SCSI_MLQUEUE_HOST_BUSY;
	}
	return rc;
}