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
struct scatterlist {int dummy; } ;
struct TYPE_2__ {struct scatterlist smp_req; } ;
struct sas_task {TYPE_1__ smp_task; struct domain_device* dev; } ;
struct hisi_sas_slot {unsigned int idx; struct hisi_sas_port* port; struct hisi_sas_cmd_hdr* cmd_hdr; struct sas_task* task; } ;
struct hisi_sas_port {int id; } ;
struct hisi_sas_device {int device_id; } ;
struct hisi_sas_cmd_hdr {void* sts_buffer_addr; void* cmd_table_addr; void* transfer_tags; void* dw2; void* dw1; void* dw0; } ;
struct hisi_hba {int dummy; } ;
struct domain_device {struct hisi_sas_device* lldd_dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned int CMD_HDR_CFL_OFF ; 
 int CMD_HDR_CMD_OFF ; 
 int CMD_HDR_DEV_ID_OFF ; 
 int CMD_HDR_DIR_OFF ; 
 int CMD_HDR_FRAME_TYPE_OFF ; 
 unsigned int CMD_HDR_IPTT_OFF ; 
 int CMD_HDR_MRFL_OFF ; 
 int CMD_HDR_PORT_OFF ; 
 int CMD_HDR_PRIORITY_OFF ; 
 int DIR_NO_DATA ; 
 int HISI_SAS_MAX_SMP_RESP_SZ ; 
 void* cpu_to_le32 (unsigned int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_status_buf_addr_dma (struct hisi_sas_slot*) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 unsigned int sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static void prep_smp_v3_hw(struct hisi_hba *hisi_hba,
			  struct hisi_sas_slot *slot)
{
	struct sas_task *task = slot->task;
	struct hisi_sas_cmd_hdr *hdr = slot->cmd_hdr;
	struct domain_device *device = task->dev;
	struct hisi_sas_port *port = slot->port;
	struct scatterlist *sg_req;
	struct hisi_sas_device *sas_dev = device->lldd_dev;
	dma_addr_t req_dma_addr;
	unsigned int req_len;

	/* req */
	sg_req = &task->smp_task.smp_req;
	req_len = sg_dma_len(sg_req);
	req_dma_addr = sg_dma_address(sg_req);

	/* create header */
	/* dw0 */
	hdr->dw0 = cpu_to_le32((port->id << CMD_HDR_PORT_OFF) |
			       (1 << CMD_HDR_PRIORITY_OFF) | /* high pri */
			       (2 << CMD_HDR_CMD_OFF)); /* smp */

	/* map itct entry */
	hdr->dw1 = cpu_to_le32((sas_dev->device_id << CMD_HDR_DEV_ID_OFF) |
			       (1 << CMD_HDR_FRAME_TYPE_OFF) |
			       (DIR_NO_DATA << CMD_HDR_DIR_OFF));

	/* dw2 */
	hdr->dw2 = cpu_to_le32((((req_len - 4) / 4) << CMD_HDR_CFL_OFF) |
			       (HISI_SAS_MAX_SMP_RESP_SZ / 4 <<
			       CMD_HDR_MRFL_OFF));

	hdr->transfer_tags = cpu_to_le32(slot->idx << CMD_HDR_IPTT_OFF);

	hdr->cmd_table_addr = cpu_to_le64(req_dma_addr);
	hdr->sts_buffer_addr = cpu_to_le64(hisi_sas_status_buf_addr_dma(slot));

}