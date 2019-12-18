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
struct scsi_cmnd {int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; TYPE_1__* device; } ;
struct hpsa_scsi_dev_t {int /*<<< orphan*/  scsi3addr; int /*<<< orphan*/  ioaccel_handle; scalar_t__ in_reset; } ;
struct ctlr_info {int dummy; } ;
struct CommandList {struct hpsa_scsi_dev_t* phys_disk; struct scsi_cmnd* scsi_cmd; } ;
struct TYPE_2__ {struct hpsa_scsi_dev_t* hostdata; } ;

/* Variables and functions */
 int hpsa_scsi_ioaccel_queue_command (struct ctlr_info*,struct CommandList*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hpsa_scsi_dev_t*) ; 

__attribute__((used)) static int hpsa_scsi_ioaccel_direct_map(struct ctlr_info *h,
	struct CommandList *c)
{
	struct scsi_cmnd *cmd = c->scsi_cmd;
	struct hpsa_scsi_dev_t *dev = cmd->device->hostdata;

	if (!dev)
		return -1;

	c->phys_disk = dev;

	if (dev->in_reset)
		return -1;

	return hpsa_scsi_ioaccel_queue_command(h, c, dev->ioaccel_handle,
		cmd->cmnd, cmd->cmd_len, dev->scsi3addr, dev);
}