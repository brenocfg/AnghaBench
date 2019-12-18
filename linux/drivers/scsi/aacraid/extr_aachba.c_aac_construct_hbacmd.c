#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct scsi_cmnd {int sc_data_direction; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; TYPE_2__* device; } ;
struct fib {scalar_t__ hw_error_pa; scalar_t__ hw_fib_va; } ;
struct aac_hba_cmd_req {int byte1; void* error_length; void* error_ptr_lo; void* error_ptr_hi; void* data_length; int /*<<< orphan*/  cdb; int /*<<< orphan*/  it_nexus; void** lun; } ;
struct aac_dev {TYPE_3__** hba_map; } ;
struct TYPE_6__ {int /*<<< orphan*/  rmw_nexus; } ;
struct TYPE_5__ {int /*<<< orphan*/  lun; TYPE_1__* host; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;

/* Variables and functions */
#define  DMA_BIDIRECTIONAL 131 
#define  DMA_FROM_DEVICE 130 
#define  DMA_NONE 129 
#define  DMA_TO_DEVICE 128 
 int /*<<< orphan*/  FW_ERROR_BUFFER_SIZE ; 
 int aac_logical_to_phys (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct aac_hba_cmd_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scmd_channel (struct scsi_cmnd*) ; 
 int scmd_id (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 

__attribute__((used)) static struct aac_hba_cmd_req *aac_construct_hbacmd(struct fib *fib,
							struct scsi_cmnd *cmd)
{
	struct aac_hba_cmd_req *hbacmd;
	struct aac_dev *dev;
	int bus, target;
	u64 address;

	dev = (struct aac_dev *)cmd->device->host->hostdata;

	hbacmd = (struct aac_hba_cmd_req *)fib->hw_fib_va;
	memset(hbacmd, 0, 96);	/* sizeof(*hbacmd) is not necessary */
	/* iu_type is a parameter of aac_hba_send */
	switch (cmd->sc_data_direction) {
	case DMA_TO_DEVICE:
		hbacmd->byte1 = 2;
		break;
	case DMA_FROM_DEVICE:
	case DMA_BIDIRECTIONAL:
		hbacmd->byte1 = 1;
		break;
	case DMA_NONE:
	default:
		break;
	}
	hbacmd->lun[1] = cpu_to_le32(cmd->device->lun);

	bus = aac_logical_to_phys(scmd_channel(cmd));
	target = scmd_id(cmd);
	hbacmd->it_nexus = dev->hba_map[bus][target].rmw_nexus;

	/* we fill in reply_qid later in aac_src_deliver_message */
	/* we fill in iu_type, request_id later in aac_hba_send */
	/* we fill in emb_data_desc_count later in aac_build_sghba */

	memcpy(hbacmd->cdb, cmd->cmnd, cmd->cmd_len);
	hbacmd->data_length = cpu_to_le32(scsi_bufflen(cmd));

	address = (u64)fib->hw_error_pa;
	hbacmd->error_ptr_hi = cpu_to_le32((u32)(address >> 32));
	hbacmd->error_ptr_lo = cpu_to_le32((u32)(address & 0xffffffff));
	hbacmd->error_length = cpu_to_le32(FW_ERROR_BUFFER_SIZE);

	return hbacmd;
}