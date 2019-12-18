#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct megasas_instance {int vf_affiliation_111_h; TYPE_8__* pdev; TYPE_9__* vf_affiliation_111; TYPE_7__* host; } ;
struct TYPE_14__ {TYPE_3__* sge32; } ;
struct TYPE_12__ {TYPE_9__* b; } ;
struct megasas_dcmd_frame {int sge_count; int /*<<< orphan*/  cmd_status; TYPE_4__ sgl; void* opcode; void* data_xfer_len; scalar_t__ pad_0; scalar_t__ timeout; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd; TYPE_2__ mbox; } ;
struct megasas_cmd {TYPE_1__* frame; } ;
struct MR_LD_VF_AFFILIATION_111 {size_t thisVf; int vdCount; TYPE_6__* map; } ;
typedef  int dma_addr_t ;
struct TYPE_19__ {TYPE_5__* map; } ;
struct TYPE_18__ {int /*<<< orphan*/  dev; } ;
struct TYPE_17__ {int /*<<< orphan*/  host_no; } ;
struct TYPE_16__ {scalar_t__* policy; } ;
struct TYPE_15__ {scalar_t__* policy; } ;
struct TYPE_13__ {void* length; void* phys_addr; } ;
struct TYPE_11__ {struct megasas_dcmd_frame dcmd; } ;

/* Variables and functions */
 scalar_t__ DCMD_SUCCESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  MFI_CMD_DCMD ; 
 int /*<<< orphan*/  MFI_FRAME_DIR_BOTH ; 
 int MFI_MBOX_SIZE ; 
 int /*<<< orphan*/  MFI_STAT_INVALID_STATUS ; 
 int MR_DCMD_LD_VF_MAP_GET_ALL_LDS_111 ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 struct MR_LD_VF_AFFILIATION_111* dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct MR_LD_VF_AFFILIATION_111*,int) ; 
 struct megasas_cmd* megasas_get_cmd (struct megasas_instance*) ; 
 scalar_t__ megasas_issue_blocked_cmd (struct megasas_instance*,struct megasas_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_return_cmd (struct megasas_instance*,struct megasas_cmd*) ; 
 int /*<<< orphan*/  memcpy (TYPE_9__*,struct MR_LD_VF_AFFILIATION_111*,int) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int megasas_get_ld_vf_affiliation_111(struct megasas_instance *instance,
					    int initial)
{
	struct megasas_cmd *cmd;
	struct megasas_dcmd_frame *dcmd;
	struct MR_LD_VF_AFFILIATION_111 *new_affiliation_111 = NULL;
	dma_addr_t new_affiliation_111_h;
	int ld, retval = 0;
	u8 thisVf;

	cmd = megasas_get_cmd(instance);

	if (!cmd) {
		dev_printk(KERN_DEBUG, &instance->pdev->dev, "megasas_get_ld_vf_affiliation_111:"
		       "Failed to get cmd for scsi%d\n",
			instance->host->host_no);
		return -ENOMEM;
	}

	dcmd = &cmd->frame->dcmd;

	if (!instance->vf_affiliation_111) {
		dev_warn(&instance->pdev->dev, "SR-IOV: Couldn't get LD/VF "
		       "affiliation for scsi%d\n", instance->host->host_no);
		megasas_return_cmd(instance, cmd);
		return -ENOMEM;
	}

	if (initial)
			memset(instance->vf_affiliation_111, 0,
			       sizeof(struct MR_LD_VF_AFFILIATION_111));
	else {
		new_affiliation_111 =
			dma_alloc_coherent(&instance->pdev->dev,
					   sizeof(struct MR_LD_VF_AFFILIATION_111),
					   &new_affiliation_111_h, GFP_KERNEL);
		if (!new_affiliation_111) {
			dev_printk(KERN_DEBUG, &instance->pdev->dev, "SR-IOV: Couldn't allocate "
			       "memory for new affiliation for scsi%d\n",
			       instance->host->host_no);
			megasas_return_cmd(instance, cmd);
			return -ENOMEM;
		}
	}

	memset(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = MFI_STAT_INVALID_STATUS;
	dcmd->sge_count = 1;
	dcmd->flags = cpu_to_le16(MFI_FRAME_DIR_BOTH);
	dcmd->timeout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len =
		cpu_to_le32(sizeof(struct MR_LD_VF_AFFILIATION_111));
	dcmd->opcode = cpu_to_le32(MR_DCMD_LD_VF_MAP_GET_ALL_LDS_111);

	if (initial)
		dcmd->sgl.sge32[0].phys_addr =
			cpu_to_le32(instance->vf_affiliation_111_h);
	else
		dcmd->sgl.sge32[0].phys_addr =
			cpu_to_le32(new_affiliation_111_h);

	dcmd->sgl.sge32[0].length = cpu_to_le32(
		sizeof(struct MR_LD_VF_AFFILIATION_111));

	dev_warn(&instance->pdev->dev, "SR-IOV: Getting LD/VF affiliation for "
	       "scsi%d\n", instance->host->host_no);

	if (megasas_issue_blocked_cmd(instance, cmd, 0) != DCMD_SUCCESS) {
		dev_warn(&instance->pdev->dev, "SR-IOV: LD/VF affiliation DCMD"
		       " failed with status 0x%x for scsi%d\n",
		       dcmd->cmd_status, instance->host->host_no);
		retval = 1; /* Do a scan if we couldn't get affiliation */
		goto out;
	}

	if (!initial) {
		thisVf = new_affiliation_111->thisVf;
		for (ld = 0 ; ld < new_affiliation_111->vdCount; ld++)
			if (instance->vf_affiliation_111->map[ld].policy[thisVf] !=
			    new_affiliation_111->map[ld].policy[thisVf]) {
				dev_warn(&instance->pdev->dev, "SR-IOV: "
				       "Got new LD/VF affiliation for scsi%d\n",
				       instance->host->host_no);
				memcpy(instance->vf_affiliation_111,
				       new_affiliation_111,
				       sizeof(struct MR_LD_VF_AFFILIATION_111));
				retval = 1;
				goto out;
			}
	}
out:
	if (new_affiliation_111) {
		dma_free_coherent(&instance->pdev->dev,
				    sizeof(struct MR_LD_VF_AFFILIATION_111),
				    new_affiliation_111,
				    new_affiliation_111_h);
	}

	megasas_return_cmd(instance, cmd);

	return retval;
}