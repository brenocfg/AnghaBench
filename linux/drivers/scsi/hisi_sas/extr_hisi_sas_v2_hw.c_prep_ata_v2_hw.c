#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_5__ {scalar_t__ command; int control; int flags; int /*<<< orphan*/  sector_count; } ;
struct TYPE_4__ {TYPE_2__ fis; int /*<<< orphan*/  device_control_reg_update; scalar_t__ use_ncq; } ;
struct sas_task {int data_dir; int total_xfer_len; TYPE_1__ ata_task; int /*<<< orphan*/  scatter; struct ata_queued_cmd* uldd_task; struct domain_device* dev; } ;
struct host_to_dev_fis {int dummy; } ;
struct hisi_sas_tmf_task {int phy_id; scalar_t__ force_phy; } ;
struct hisi_sas_slot {int idx; int /*<<< orphan*/  n_elem; struct hisi_sas_tmf_task* tmf; struct hisi_sas_cmd_hdr* cmd_hdr; struct sas_task* task; } ;
struct hisi_sas_port {int id; } ;
struct hisi_sas_device {int device_id; } ;
struct hisi_sas_cmd_hdr {void* sts_buffer_addr; void* cmd_table_addr; void* data_transfer_len; void* transfer_tags; void* dw2; void* dw1; void* dw0; } ;
struct hisi_hba {int dummy; } ;
struct domain_device {int /*<<< orphan*/  dev_type; struct asd_sas_port* port; struct hisi_sas_device* lldd_dev; struct domain_device* parent; } ;
struct ata_queued_cmd {int tag; } ;
struct asd_sas_port {int dummy; } ;

/* Variables and functions */
 scalar_t__ ATA_CMD_DEV_RESET ; 
 int ATA_SRST ; 
 int CMD_HDR_CFL_OFF ; 
 int CMD_HDR_CMD_OFF ; 
 int CMD_HDR_DEV_ID_OFF ; 
 int CMD_HDR_DIR_MSK ; 
 int CMD_HDR_DIR_OFF ; 
 int CMD_HDR_FORCE_PHY_MSK ; 
 int CMD_HDR_FRAME_TYPE_OFF ; 
 int CMD_HDR_NCQ_TAG_OFF ; 
 int CMD_HDR_PHY_ID_OFF ; 
 int CMD_HDR_PORT_OFF ; 
 int CMD_HDR_RESET_OFF ; 
 int CMD_HDR_SG_MOD_OFF ; 
 int DIR_TO_DEVICE ; 
 int DIR_TO_INI ; 
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 int HISI_SAS_MAX_STP_RESP_SZ ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 scalar_t__ dev_is_expander (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_cmd_hdr_addr_dma (struct hisi_sas_slot*) ; 
 int /*<<< orphan*/ * hisi_sas_cmd_hdr_addr_mem (struct hisi_sas_slot*) ; 
 int hisi_sas_get_ata_protocol (TYPE_2__*,int) ; 
 int /*<<< orphan*/  hisi_sas_status_buf_addr_dma (struct hisi_sas_slot*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  prep_prd_sge_v2_hw (struct hisi_hba*,struct hisi_sas_slot*,struct hisi_sas_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hisi_sas_port* to_hisi_sas_port (struct asd_sas_port*) ; 

__attribute__((used)) static void prep_ata_v2_hw(struct hisi_hba *hisi_hba,
			  struct hisi_sas_slot *slot)
{
	struct sas_task *task = slot->task;
	struct domain_device *device = task->dev;
	struct domain_device *parent_dev = device->parent;
	struct hisi_sas_device *sas_dev = device->lldd_dev;
	struct hisi_sas_cmd_hdr *hdr = slot->cmd_hdr;
	struct asd_sas_port *sas_port = device->port;
	struct hisi_sas_port *port = to_hisi_sas_port(sas_port);
	struct hisi_sas_tmf_task *tmf = slot->tmf;
	u8 *buf_cmd;
	int has_data = 0, hdr_tag = 0;
	u32 dw0, dw1 = 0, dw2 = 0;

	/* create header */
	/* dw0 */
	dw0 = port->id << CMD_HDR_PORT_OFF;
	if (parent_dev && dev_is_expander(parent_dev->dev_type))
		dw0 |= 3 << CMD_HDR_CMD_OFF;
	else
		dw0 |= 4 << CMD_HDR_CMD_OFF;

	if (tmf && tmf->force_phy) {
		dw0 |= CMD_HDR_FORCE_PHY_MSK;
		dw0 |= (1 << tmf->phy_id) << CMD_HDR_PHY_ID_OFF;
	}

	hdr->dw0 = cpu_to_le32(dw0);

	/* dw1 */
	switch (task->data_dir) {
	case DMA_TO_DEVICE:
		has_data = 1;
		dw1 |= DIR_TO_DEVICE << CMD_HDR_DIR_OFF;
		break;
	case DMA_FROM_DEVICE:
		has_data = 1;
		dw1 |= DIR_TO_INI << CMD_HDR_DIR_OFF;
		break;
	default:
		dw1 &= ~CMD_HDR_DIR_MSK;
	}

	if ((task->ata_task.fis.command == ATA_CMD_DEV_RESET) &&
			(task->ata_task.fis.control & ATA_SRST))
		dw1 |= 1 << CMD_HDR_RESET_OFF;

	dw1 |= (hisi_sas_get_ata_protocol(
		&task->ata_task.fis, task->data_dir))
		<< CMD_HDR_FRAME_TYPE_OFF;
	dw1 |= sas_dev->device_id << CMD_HDR_DEV_ID_OFF;
	hdr->dw1 = cpu_to_le32(dw1);

	/* dw2 */
	if (task->ata_task.use_ncq) {
		struct ata_queued_cmd *qc = task->uldd_task;

		hdr_tag = qc->tag;
		task->ata_task.fis.sector_count |= (u8) (hdr_tag << 3);
		dw2 |= hdr_tag << CMD_HDR_NCQ_TAG_OFF;
	}

	dw2 |= (HISI_SAS_MAX_STP_RESP_SZ / 4) << CMD_HDR_CFL_OFF |
			2 << CMD_HDR_SG_MOD_OFF;
	hdr->dw2 = cpu_to_le32(dw2);

	/* dw3 */
	hdr->transfer_tags = cpu_to_le32(slot->idx);

	if (has_data)
		prep_prd_sge_v2_hw(hisi_hba, slot, hdr, task->scatter,
					slot->n_elem);

	hdr->data_transfer_len = cpu_to_le32(task->total_xfer_len);
	hdr->cmd_table_addr = cpu_to_le64(hisi_sas_cmd_hdr_addr_dma(slot));
	hdr->sts_buffer_addr = cpu_to_le64(hisi_sas_status_buf_addr_dma(slot));

	buf_cmd = hisi_sas_cmd_hdr_addr_mem(slot);

	if (likely(!task->ata_task.device_control_reg_update))
		task->ata_task.fis.flags |= 0x80; /* C=1: update ATA cmd reg */
	/* fill in command FIS */
	memcpy(buf_cmd, &task->ata_task.fis, sizeof(struct host_to_dev_fis));
}