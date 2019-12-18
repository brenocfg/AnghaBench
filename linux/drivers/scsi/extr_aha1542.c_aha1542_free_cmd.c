#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
struct device {int dummy; } ;
struct chain {int dummy; } ;
struct aha1542_cmd {int /*<<< orphan*/ * chain; int /*<<< orphan*/  chain_handle; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {struct device* dma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct aha1542_cmd* scsi_cmd_priv (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int scsi_sg_count (struct scsi_cmnd*) ; 

__attribute__((used)) static void aha1542_free_cmd(struct scsi_cmnd *cmd)
{
	struct aha1542_cmd *acmd = scsi_cmd_priv(cmd);
	struct device *dev = cmd->device->host->dma_dev;
	size_t len = scsi_sg_count(cmd) * sizeof(struct chain);

	if (acmd->chain) {
		dma_unmap_single(dev, acmd->chain_handle, len, DMA_TO_DEVICE);
		kfree(acmd->chain);
	}

	acmd->chain = NULL;
	scsi_dma_unmap(cmd);
}