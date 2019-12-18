#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sas_task {struct domain_device* dev; } ;
struct hisi_sas_slot {int idx; struct hisi_sas_port* port; struct hisi_sas_cmd_hdr* cmd_hdr; struct sas_task* task; } ;
struct hisi_sas_port {unsigned int id; } ;
struct hisi_sas_cmd_hdr {void* transfer_tags; void* dw7; void* dw1; void* dw0; } ;
struct hisi_hba {int dummy; } ;
struct domain_device {int dummy; } ;

/* Variables and functions */
 unsigned int CMD_HDR_ABORT_DEVICE_TYPE_OFF ; 
 int CMD_HDR_ABORT_FLAG_OFF ; 
 int CMD_HDR_ABORT_IPTT_OFF ; 
 unsigned int CMD_HDR_CMD_OFF ; 
 int CMD_HDR_DEV_ID_OFF ; 
 unsigned int CMD_HDR_PORT_OFF ; 
 void* cpu_to_le32 (int) ; 
 unsigned int dev_is_sata (struct domain_device*) ; 

__attribute__((used)) static void prep_abort_v3_hw(struct hisi_hba *hisi_hba,
		struct hisi_sas_slot *slot,
		int device_id, int abort_flag, int tag_to_abort)
{
	struct sas_task *task = slot->task;
	struct domain_device *dev = task->dev;
	struct hisi_sas_cmd_hdr *hdr = slot->cmd_hdr;
	struct hisi_sas_port *port = slot->port;

	/* dw0 */
	hdr->dw0 = cpu_to_le32((5U << CMD_HDR_CMD_OFF) | /*abort*/
			       (port->id << CMD_HDR_PORT_OFF) |
				   (dev_is_sata(dev)
					<< CMD_HDR_ABORT_DEVICE_TYPE_OFF) |
					(abort_flag
					 << CMD_HDR_ABORT_FLAG_OFF));

	/* dw1 */
	hdr->dw1 = cpu_to_le32(device_id
			<< CMD_HDR_DEV_ID_OFF);

	/* dw7 */
	hdr->dw7 = cpu_to_le32(tag_to_abort << CMD_HDR_ABORT_IPTT_OFF);
	hdr->transfer_tags = cpu_to_le32(slot->idx);

}