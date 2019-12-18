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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_8__ {int /*<<< orphan*/ * ptr; } ;
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_4__ SCp; } ;
struct megasas_instance {int /*<<< orphan*/  ldio_outstanding; scalar_t__ ldio_threshold; struct fusion_context* ctrl_context; } ;
struct megasas_cmd_fusion {scalar_t__* sense; int cmd_completed; TYPE_3__* io_request; struct scsi_cmnd* scmd; } ;
struct fusion_context {struct megasas_cmd_fusion** cmd_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  peer_smid; } ;
struct RAID_CONTEXT_G35 {scalar_t__ status; scalar_t__ ex_status; TYPE_1__ flow_specific; } ;
struct TYPE_6__ {struct RAID_CONTEXT_G35 raid_context_g35; } ;
struct TYPE_7__ {int /*<<< orphan*/  DataLength; TYPE_2__ RaidContext; } ;

/* Variables and functions */
 scalar_t__ MFI_STAT_OK ; 
 scalar_t__ READ_WRITE_LDIO ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_cmd_status (struct fusion_context*,struct scsi_cmnd*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ megasas_cmd_type (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  megasas_return_cmd_fusion (struct megasas_instance*,struct megasas_cmd_fusion*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static inline void
megasas_complete_r1_command(struct megasas_instance *instance,
			    struct megasas_cmd_fusion *cmd)
{
	u8 *sense, status, ex_status;
	u32 data_length;
	u16 peer_smid;
	struct fusion_context *fusion;
	struct megasas_cmd_fusion *r1_cmd = NULL;
	struct scsi_cmnd *scmd_local = NULL;
	struct RAID_CONTEXT_G35 *rctx_g35;

	rctx_g35 = &cmd->io_request->RaidContext.raid_context_g35;
	fusion = instance->ctrl_context;
	peer_smid = le16_to_cpu(rctx_g35->flow_specific.peer_smid);

	r1_cmd = fusion->cmd_list[peer_smid - 1];
	scmd_local = cmd->scmd;
	status = rctx_g35->status;
	ex_status = rctx_g35->ex_status;
	data_length = cmd->io_request->DataLength;
	sense = cmd->sense;

	cmd->cmd_completed = true;

	/* Check if peer command is completed or not*/
	if (r1_cmd->cmd_completed) {
		rctx_g35 = &r1_cmd->io_request->RaidContext.raid_context_g35;
		if (rctx_g35->status != MFI_STAT_OK) {
			status = rctx_g35->status;
			ex_status = rctx_g35->ex_status;
			data_length = r1_cmd->io_request->DataLength;
			sense = r1_cmd->sense;
		}

		megasas_return_cmd_fusion(instance, r1_cmd);
		map_cmd_status(fusion, scmd_local, status, ex_status,
			       le32_to_cpu(data_length), sense);
		if (instance->ldio_threshold &&
		    megasas_cmd_type(scmd_local) == READ_WRITE_LDIO)
			atomic_dec(&instance->ldio_outstanding);
		scmd_local->SCp.ptr = NULL;
		megasas_return_cmd_fusion(instance, cmd);
		scsi_dma_unmap(scmd_local);
		scmd_local->scsi_done(scmd_local);
	}
}