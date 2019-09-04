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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_recv_msg {void* msg_id; void* msg_len; void* async_mgmt_to_pf; void* mod; void* cmd; scalar_t__ msg; } ;
struct hinic_pf_to_mgmt {struct hinic_hwif* hwif; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_MGMT_TO_PF ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  DIRECTION ; 
 void* HINIC_MSG_HEADER_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAST ; 
 int MAX_MSG_LEN ; 
 void* MGMT_RESP ; 
 int /*<<< orphan*/  MODULE ; 
 int /*<<< orphan*/  MSG_ID ; 
 int /*<<< orphan*/  MSG_LEN ; 
 int SEGMENT_LEN ; 
 int /*<<< orphan*/  SEG_LEN ; 
 int /*<<< orphan*/  SEQID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mgmt_recv_msg_handler (struct hinic_pf_to_mgmt*,struct hinic_recv_msg*) ; 
 int /*<<< orphan*/  mgmt_resp_msg_handler (struct hinic_pf_to_mgmt*,struct hinic_recv_msg*) ; 

__attribute__((used)) static void recv_mgmt_msg_handler(struct hinic_pf_to_mgmt *pf_to_mgmt,
				  u64 *header, struct hinic_recv_msg *recv_msg)
{
	struct hinic_hwif *hwif = pf_to_mgmt->hwif;
	struct pci_dev *pdev = hwif->pdev;
	int seq_id, seg_len;
	u8 *msg_body;

	seq_id = HINIC_MSG_HEADER_GET(*header, SEQID);
	seg_len = HINIC_MSG_HEADER_GET(*header, SEG_LEN);

	if (seq_id >= (MAX_MSG_LEN / SEGMENT_LEN)) {
		dev_err(&pdev->dev, "recv big mgmt msg\n");
		return;
	}

	msg_body = (u8 *)header + sizeof(*header);
	memcpy(recv_msg->msg + seq_id * SEGMENT_LEN, msg_body, seg_len);

	if (!HINIC_MSG_HEADER_GET(*header, LAST))
		return;

	recv_msg->cmd = HINIC_MSG_HEADER_GET(*header, CMD);
	recv_msg->mod = HINIC_MSG_HEADER_GET(*header, MODULE);
	recv_msg->async_mgmt_to_pf = HINIC_MSG_HEADER_GET(*header,
							  ASYNC_MGMT_TO_PF);
	recv_msg->msg_len = HINIC_MSG_HEADER_GET(*header, MSG_LEN);
	recv_msg->msg_id = HINIC_MSG_HEADER_GET(*header, MSG_ID);

	if (HINIC_MSG_HEADER_GET(*header, DIRECTION) == MGMT_RESP)
		mgmt_resp_msg_handler(pf_to_mgmt, recv_msg);
	else
		mgmt_recv_msg_handler(pf_to_mgmt, recv_msg);
}