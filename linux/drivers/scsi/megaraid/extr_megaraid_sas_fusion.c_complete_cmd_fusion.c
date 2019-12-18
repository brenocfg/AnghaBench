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
struct TYPE_6__ {scalar_t__ low; scalar_t__ high; } ;
union desc_value {int /*<<< orphan*/  word; TYPE_1__ u; } ;
union MPI2_REPLY_DESCRIPTORS_UNION {int /*<<< orphan*/  Words; } ;
typedef  int u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct TYPE_10__ {int Status; int /*<<< orphan*/ * ptr; } ;
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_5__ SCp; } ;
struct megasas_irq_context {int irq_poll_scheduled; int irq_line_enable; int /*<<< orphan*/  irqpoll; } ;
struct megasas_instance {int threshold_reply_count; int /*<<< orphan*/ * reply_post_host_index_addr; scalar_t__ msix_combined; struct megasas_cmd** cmd_list; int /*<<< orphan*/  ldio_outstanding; int /*<<< orphan*/  ldio_threshold; int /*<<< orphan*/  fw_outstanding; TYPE_4__* pdev; int /*<<< orphan*/  adprecovery; struct fusion_context* ctrl_context; } ;
struct megasas_cmd_fusion {int* sense; size_t pd_r1_lb; size_t sync_cmd_idx; int /*<<< orphan*/  r1_alt_dev_handle; struct scsi_cmnd* scmd; int /*<<< orphan*/  done; scalar_t__ io_request; } ;
struct megasas_cmd {int flags; } ;
struct fusion_context {int* last_reply_idx; int reply_q_depth; union MPI2_REPLY_DESCRIPTORS_UNION** reply_frames_desc; struct LD_LOAD_BALANCE_INFO* load_balance_info; struct megasas_cmd_fusion** cmd_list; } ;
struct MR_TASK_MANAGE_REQUEST {int /*<<< orphan*/  TmRequest; } ;
struct MPI2_SCSI_TASK_MANAGE_REQUEST {int /*<<< orphan*/  TaskMID; int /*<<< orphan*/  TaskType; } ;
struct MPI2_SCSI_IO_SUCCESS_REPLY_DESCRIPTOR {int ReplyFlags; int /*<<< orphan*/  SMID; } ;
struct TYPE_7__ {int status; int ex_status; } ;
struct TYPE_8__ {TYPE_2__ raid_context; } ;
struct MPI2_RAID_SCSI_IO_REQUEST {size_t DataLength; int Function; TYPE_3__ RaidContext; } ;
struct LD_LOAD_BALANCE_INFO {int /*<<< orphan*/ * scsi_pending_cmds; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_OK ; 
 int DRV_DCMD_POLLED_MODE ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 size_t MEGASAS_DEV_INDEX (struct scsi_cmnd*) ; 
 scalar_t__ MEGASAS_HW_CRITICAL_ERROR ; 
 int MEGASAS_LOAD_BALANCE_FLAG ; 
#define  MEGASAS_MPI2_FUNCTION_LD_IO_REQUEST 131 
#define  MEGASAS_MPI2_FUNCTION_PASSTHRU_IO_REQUEST 130 
#define  MPI2_FUNCTION_SCSI_IO_REQUEST 129 
#define  MPI2_FUNCTION_SCSI_TASK_MGMT 128 
 int MPI2_RPY_DESCRIPT_FLAGS_TYPE_MASK ; 
 int MPI2_RPY_DESCRIPT_FLAGS_UNUSED ; 
 int /*<<< orphan*/  MR_DEVHANDLE_INVALID ; 
 int /*<<< orphan*/  READ_WRITE_LDIO ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  ULLONG_MAX ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_poll_sched (int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (size_t) ; 
 int /*<<< orphan*/  map_cmd_status (struct fusion_context*,struct scsi_cmnd*,int,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  megasas_check_and_restore_queue_depth (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_cmd_type (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  megasas_complete_cmd (struct megasas_instance*,struct megasas_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_complete_r1_command (struct megasas_instance*,struct megasas_cmd_fusion*) ; 
 int /*<<< orphan*/  megasas_return_cmd (struct megasas_instance*,struct megasas_cmd*) ; 
 int /*<<< orphan*/  megasas_return_cmd_fusion (struct megasas_instance*,struct megasas_cmd_fusion*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
complete_cmd_fusion(struct megasas_instance *instance, u32 MSIxIndex,
		    struct megasas_irq_context *irq_context)
{
	union MPI2_REPLY_DESCRIPTORS_UNION *desc;
	struct MPI2_SCSI_IO_SUCCESS_REPLY_DESCRIPTOR *reply_desc;
	struct MPI2_RAID_SCSI_IO_REQUEST *scsi_io_req;
	struct fusion_context *fusion;
	struct megasas_cmd *cmd_mfi;
	struct megasas_cmd_fusion *cmd_fusion;
	u16 smid, num_completed;
	u8 reply_descript_type, *sense, status, extStatus;
	u32 device_id, data_length;
	union desc_value d_val;
	struct LD_LOAD_BALANCE_INFO *lbinfo;
	int threshold_reply_count = 0;
	struct scsi_cmnd *scmd_local = NULL;
	struct MR_TASK_MANAGE_REQUEST *mr_tm_req;
	struct MPI2_SCSI_TASK_MANAGE_REQUEST *mpi_tm_req;

	fusion = instance->ctrl_context;

	if (atomic_read(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR)
		return IRQ_HANDLED;

	desc = fusion->reply_frames_desc[MSIxIndex] +
				fusion->last_reply_idx[MSIxIndex];

	reply_desc = (struct MPI2_SCSI_IO_SUCCESS_REPLY_DESCRIPTOR *)desc;

	d_val.word = desc->Words;

	reply_descript_type = reply_desc->ReplyFlags &
		MPI2_RPY_DESCRIPT_FLAGS_TYPE_MASK;

	if (reply_descript_type == MPI2_RPY_DESCRIPT_FLAGS_UNUSED)
		return IRQ_NONE;

	num_completed = 0;

	while (d_val.u.low != cpu_to_le32(UINT_MAX) &&
	       d_val.u.high != cpu_to_le32(UINT_MAX)) {

		smid = le16_to_cpu(reply_desc->SMID);
		cmd_fusion = fusion->cmd_list[smid - 1];
		scsi_io_req = (struct MPI2_RAID_SCSI_IO_REQUEST *)
						cmd_fusion->io_request;

		scmd_local = cmd_fusion->scmd;
		status = scsi_io_req->RaidContext.raid_context.status;
		extStatus = scsi_io_req->RaidContext.raid_context.ex_status;
		sense = cmd_fusion->sense;
		data_length = scsi_io_req->DataLength;

		switch (scsi_io_req->Function) {
		case MPI2_FUNCTION_SCSI_TASK_MGMT:
			mr_tm_req = (struct MR_TASK_MANAGE_REQUEST *)
						cmd_fusion->io_request;
			mpi_tm_req = (struct MPI2_SCSI_TASK_MANAGE_REQUEST *)
						&mr_tm_req->TmRequest;
			dev_dbg(&instance->pdev->dev, "TM completion:"
				"type: 0x%x TaskMID: 0x%x\n",
				mpi_tm_req->TaskType, mpi_tm_req->TaskMID);
			complete(&cmd_fusion->done);
			break;
		case MPI2_FUNCTION_SCSI_IO_REQUEST:  /*Fast Path IO.*/
			/* Update load balancing info */
			if (fusion->load_balance_info &&
			    (cmd_fusion->scmd->SCp.Status &
			    MEGASAS_LOAD_BALANCE_FLAG)) {
				device_id = MEGASAS_DEV_INDEX(scmd_local);
				lbinfo = &fusion->load_balance_info[device_id];
				atomic_dec(&lbinfo->scsi_pending_cmds[cmd_fusion->pd_r1_lb]);
				cmd_fusion->scmd->SCp.Status &= ~MEGASAS_LOAD_BALANCE_FLAG;
			}
			/* Fall through - and complete IO */
		case MEGASAS_MPI2_FUNCTION_LD_IO_REQUEST: /* LD-IO Path */
			atomic_dec(&instance->fw_outstanding);
			if (cmd_fusion->r1_alt_dev_handle == MR_DEVHANDLE_INVALID) {
				map_cmd_status(fusion, scmd_local, status,
					       extStatus, le32_to_cpu(data_length),
					       sense);
				if (instance->ldio_threshold &&
				    (megasas_cmd_type(scmd_local) == READ_WRITE_LDIO))
					atomic_dec(&instance->ldio_outstanding);
				scmd_local->SCp.ptr = NULL;
				megasas_return_cmd_fusion(instance, cmd_fusion);
				scsi_dma_unmap(scmd_local);
				scmd_local->scsi_done(scmd_local);
			} else	/* Optimal VD - R1 FP command completion. */
				megasas_complete_r1_command(instance, cmd_fusion);
			break;
		case MEGASAS_MPI2_FUNCTION_PASSTHRU_IO_REQUEST: /*MFI command */
			cmd_mfi = instance->cmd_list[cmd_fusion->sync_cmd_idx];
			/* Poll mode. Dummy free.
			 * In case of Interrupt mode, caller has reverse check.
			 */
			if (cmd_mfi->flags & DRV_DCMD_POLLED_MODE) {
				cmd_mfi->flags &= ~DRV_DCMD_POLLED_MODE;
				megasas_return_cmd(instance, cmd_mfi);
			} else
				megasas_complete_cmd(instance, cmd_mfi, DID_OK);
			break;
		}

		fusion->last_reply_idx[MSIxIndex]++;
		if (fusion->last_reply_idx[MSIxIndex] >=
		    fusion->reply_q_depth)
			fusion->last_reply_idx[MSIxIndex] = 0;

		desc->Words = cpu_to_le64(ULLONG_MAX);
		num_completed++;
		threshold_reply_count++;

		/* Get the next reply descriptor */
		if (!fusion->last_reply_idx[MSIxIndex])
			desc = fusion->reply_frames_desc[MSIxIndex];
		else
			desc++;

		reply_desc =
		  (struct MPI2_SCSI_IO_SUCCESS_REPLY_DESCRIPTOR *)desc;

		d_val.word = desc->Words;

		reply_descript_type = reply_desc->ReplyFlags &
			MPI2_RPY_DESCRIPT_FLAGS_TYPE_MASK;

		if (reply_descript_type == MPI2_RPY_DESCRIPT_FLAGS_UNUSED)
			break;
		/*
		 * Write to reply post host index register after completing threshold
		 * number of reply counts and still there are more replies in reply queue
		 * pending to be completed
		 */
		if (threshold_reply_count >= instance->threshold_reply_count) {
			if (instance->msix_combined)
				writel(((MSIxIndex & 0x7) << 24) |
					fusion->last_reply_idx[MSIxIndex],
					instance->reply_post_host_index_addr[MSIxIndex/8]);
			else
				writel((MSIxIndex << 24) |
					fusion->last_reply_idx[MSIxIndex],
					instance->reply_post_host_index_addr[0]);
			threshold_reply_count = 0;
			if (irq_context) {
				if (!irq_context->irq_poll_scheduled) {
					irq_context->irq_poll_scheduled = true;
					irq_context->irq_line_enable = true;
					irq_poll_sched(&irq_context->irqpoll);
				}
				return num_completed;
			}
		}
	}

	if (num_completed) {
		wmb();
		if (instance->msix_combined)
			writel(((MSIxIndex & 0x7) << 24) |
				fusion->last_reply_idx[MSIxIndex],
				instance->reply_post_host_index_addr[MSIxIndex/8]);
		else
			writel((MSIxIndex << 24) |
				fusion->last_reply_idx[MSIxIndex],
				instance->reply_post_host_index_addr[0]);
		megasas_check_and_restore_queue_depth(instance);
	}
	return num_completed;
}