#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct megasas_instance {scalar_t__ adapter_type; TYPE_4__* host; TYPE_3__* pdev; int /*<<< orphan*/  mask_interrupts; int /*<<< orphan*/  hb_host_mem_h; int /*<<< orphan*/  hb_host_mem; } ;
struct TYPE_6__ {void** s; int /*<<< orphan*/  b; } ;
struct megasas_dcmd_frame {scalar_t__ cmd_status; int sge_count; void* opcode; void* data_xfer_len; scalar_t__ pad_0; scalar_t__ timeout; void* flags; int /*<<< orphan*/  cmd; TYPE_2__ mbox; } ;
struct megasas_cmd {TYPE_1__* frame; } ;
struct MR_CTRL_HB_HOST_MEM {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  host_no; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct megasas_dcmd_frame dcmd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  MEGASAS_ROUTINE_WAIT_TIME_VF ; 
 int /*<<< orphan*/  MFI_CMD_DCMD ; 
 int MFI_FRAME_DIR_BOTH ; 
 int /*<<< orphan*/  MFI_MBOX_SIZE ; 
 scalar_t__ MFI_SERIES ; 
 scalar_t__ MFI_STAT_INVALID_STATUS ; 
 int MR_DCMD_CTRL_SHARED_HOST_MEM_ALLOC ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct megasas_cmd* megasas_get_cmd (struct megasas_instance*) ; 
 int megasas_issue_blocked_cmd (struct megasas_instance*,struct megasas_cmd*,int /*<<< orphan*/ ) ; 
 int megasas_issue_polled (struct megasas_instance*,struct megasas_cmd*) ; 
 int /*<<< orphan*/  megasas_return_cmd (struct megasas_instance*,struct megasas_cmd*) ; 
 int /*<<< orphan*/  megasas_set_dma_settings (struct megasas_instance*,struct megasas_dcmd_frame*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int megasas_sriov_start_heartbeat(struct megasas_instance *instance,
					 int initial)
{
	struct megasas_cmd *cmd;
	struct megasas_dcmd_frame *dcmd;
	int retval = 0;

	cmd = megasas_get_cmd(instance);

	if (!cmd) {
		dev_printk(KERN_DEBUG, &instance->pdev->dev, "megasas_sriov_start_heartbeat: "
		       "Failed to get cmd for scsi%d\n",
		       instance->host->host_no);
		return -ENOMEM;
	}

	dcmd = &cmd->frame->dcmd;

	if (initial) {
		instance->hb_host_mem =
			dma_alloc_coherent(&instance->pdev->dev,
					   sizeof(struct MR_CTRL_HB_HOST_MEM),
					   &instance->hb_host_mem_h,
					   GFP_KERNEL);
		if (!instance->hb_host_mem) {
			dev_printk(KERN_DEBUG, &instance->pdev->dev, "SR-IOV: Couldn't allocate"
			       " memory for heartbeat host memory for scsi%d\n",
			       instance->host->host_no);
			retval = -ENOMEM;
			goto out;
		}
	}

	memset(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->mbox.s[0] = cpu_to_le16(sizeof(struct MR_CTRL_HB_HOST_MEM));
	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = MFI_STAT_INVALID_STATUS;
	dcmd->sge_count = 1;
	dcmd->flags = cpu_to_le16(MFI_FRAME_DIR_BOTH);
	dcmd->timeout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = cpu_to_le32(sizeof(struct MR_CTRL_HB_HOST_MEM));
	dcmd->opcode = cpu_to_le32(MR_DCMD_CTRL_SHARED_HOST_MEM_ALLOC);

	megasas_set_dma_settings(instance, dcmd, instance->hb_host_mem_h,
				 sizeof(struct MR_CTRL_HB_HOST_MEM));

	dev_warn(&instance->pdev->dev, "SR-IOV: Starting heartbeat for scsi%d\n",
	       instance->host->host_no);

	if ((instance->adapter_type != MFI_SERIES) &&
	    !instance->mask_interrupts)
		retval = megasas_issue_blocked_cmd(instance, cmd,
			MEGASAS_ROUTINE_WAIT_TIME_VF);
	else
		retval = megasas_issue_polled(instance, cmd);

	if (retval) {
		dev_warn(&instance->pdev->dev, "SR-IOV: MR_DCMD_CTRL_SHARED_HOST"
			"_MEM_ALLOC DCMD %s for scsi%d\n",
			(dcmd->cmd_status == MFI_STAT_INVALID_STATUS) ?
			"timed out" : "failed", instance->host->host_no);
		retval = 1;
	}

out:
	megasas_return_cmd(instance, cmd);

	return retval;
}