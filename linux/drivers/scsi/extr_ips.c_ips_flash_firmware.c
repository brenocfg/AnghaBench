#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_31__ {void* buffer_addr; int /*<<< orphan*/  command_id; } ;
struct TYPE_25__ {TYPE_6__ flashfw; } ;
struct TYPE_28__ {int /*<<< orphan*/  list; } ;
struct TYPE_33__ {TYPE_7__* scsi_cmd; scalar_t__ timeout; scalar_t__ data_busaddr; TYPE_13__ cmd; int /*<<< orphan*/  flags; scalar_t__ data_len; int /*<<< orphan*/  callback; scalar_t__ op_code; scalar_t__ sg_len; int /*<<< orphan*/  lun; int /*<<< orphan*/  target_id; int /*<<< orphan*/  bus; int /*<<< orphan*/  scb_busaddr; TYPE_3__ sg_list; } ;
typedef  TYPE_8__ ips_scb_t ;
struct TYPE_26__ {scalar_t__ type; scalar_t__ direction; void* count; int /*<<< orphan*/  op_code; } ;
struct TYPE_24__ {TYPE_1__ flashfw; } ;
struct TYPE_27__ {TYPE_12__ cmd; } ;
struct TYPE_34__ {int BasicStatus; int ExtendedStatus; scalar_t__ TimeOut; TYPE_2__ CoppCP; } ;
typedef  TYPE_9__ ips_passthru_t ;
struct TYPE_22__ {int /*<<< orphan*/  flash_data; TYPE_5__* pcidev; scalar_t__ flash_datasize; } ;
typedef  TYPE_10__ ips_ha_t ;
struct TYPE_32__ {int result; TYPE_4__* device; } ;
struct TYPE_30__ {int /*<<< orphan*/  dev; } ;
struct TYPE_29__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; } ;
struct TYPE_23__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_11__ IPS_SG_LIST ;
typedef  int /*<<< orphan*/  IPS_IOCTL_CMD ;
typedef  int /*<<< orphan*/  IPS_HOST_COMMAND ;

/* Variables and functions */
 int DID_OK ; 
 int /*<<< orphan*/  IPS_CMD_DOWNLOAD ; 
 int /*<<< orphan*/  IPS_COMMAND_ID (TYPE_10__*,TYPE_8__*) ; 
 int /*<<< orphan*/  IPS_DMA_DIR (TYPE_8__*) ; 
 int IPS_FAILURE ; 
 scalar_t__ IPS_FW_IMAGE ; 
 int /*<<< orphan*/  IPS_SCB_MAP_SINGLE ; 
 int IPS_SUCCESS ; 
 scalar_t__ IPS_WRITE_FW ; 
 void* cpu_to_le32 (scalar_t__) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ips_cmd_timeout ; 
 int /*<<< orphan*/  ips_free_flash_copperhead (TYPE_10__*) ; 
 int /*<<< orphan*/  ipsintr_done ; 
 int /*<<< orphan*/  memcpy (TYPE_13__*,TYPE_12__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_12__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ips_flash_firmware(ips_ha_t * ha, ips_passthru_t * pt, ips_scb_t * scb)
{
	IPS_SG_LIST sg_list;
	uint32_t cmd_busaddr;

	if (pt->CoppCP.cmd.flashfw.type == IPS_FW_IMAGE &&
	    pt->CoppCP.cmd.flashfw.direction == IPS_WRITE_FW) {
		memset(&pt->CoppCP.cmd, 0, sizeof (IPS_HOST_COMMAND));
		pt->CoppCP.cmd.flashfw.op_code = IPS_CMD_DOWNLOAD;
		pt->CoppCP.cmd.flashfw.count = cpu_to_le32(ha->flash_datasize);
	} else {
		pt->BasicStatus = 0x0B;
		pt->ExtendedStatus = 0x00;
		ips_free_flash_copperhead(ha);
		return IPS_FAILURE;
	}
	/* Save the S/G list pointer so it doesn't get clobbered */
	sg_list.list = scb->sg_list.list;
	cmd_busaddr = scb->scb_busaddr;
	/* copy in the CP */
	memcpy(&scb->cmd, &pt->CoppCP.cmd, sizeof (IPS_IOCTL_CMD));
	/* FIX stuff that might be wrong */
	scb->sg_list.list = sg_list.list;
	scb->scb_busaddr = cmd_busaddr;
	scb->bus = scb->scsi_cmd->device->channel;
	scb->target_id = scb->scsi_cmd->device->id;
	scb->lun = scb->scsi_cmd->device->lun;
	scb->sg_len = 0;
	scb->data_len = 0;
	scb->flags = 0;
	scb->op_code = 0;
	scb->callback = ipsintr_done;
	scb->timeout = ips_cmd_timeout;

	scb->data_len = ha->flash_datasize;
	scb->data_busaddr =
	    dma_map_single(&ha->pcidev->dev, ha->flash_data, scb->data_len,
			   IPS_DMA_DIR(scb));
	scb->flags |= IPS_SCB_MAP_SINGLE;
	scb->cmd.flashfw.command_id = IPS_COMMAND_ID(ha, scb);
	scb->cmd.flashfw.buffer_addr = cpu_to_le32(scb->data_busaddr);
	if (pt->TimeOut)
		scb->timeout = pt->TimeOut;
	scb->scsi_cmd->result = DID_OK << 16;
	return IPS_SUCCESS;
}