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
typedef  scalar_t__ u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct completion {int dummy; } ;
struct hinic_recv_msg {scalar_t__ msg_id; scalar_t__ msg_len; int /*<<< orphan*/  msg; struct completion recv_done; } ;
struct hinic_pf_to_mgmt {int /*<<< orphan*/  sync_msg_lock; struct hinic_recv_msg recv_resp_msg_from_mgmt; struct hinic_hwif* hwif; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
typedef  enum mgmt_direction_type { ____Placeholder_mgmt_direction_type } mgmt_direction_type ;
typedef  enum hinic_mod_type { ____Placeholder_hinic_mod_type } hinic_mod_type ;

/* Variables and functions */
 int EFAULT ; 
 int ETIMEDOUT ; 
 scalar_t__ MAX_PF_MGMT_BUF_SIZE ; 
 int /*<<< orphan*/  MGMT_MSG_TIMEOUT ; 
 int /*<<< orphan*/  MSG_ACK ; 
 scalar_t__ MSG_NOT_RESP ; 
 scalar_t__ SYNC_MSG_ID (struct hinic_pf_to_mgmt*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int send_msg_to_mgmt (struct hinic_pf_to_mgmt*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msg_to_mgmt_sync(struct hinic_pf_to_mgmt *pf_to_mgmt,
			    enum hinic_mod_type mod, u8 cmd,
			    u8 *buf_in, u16 in_size,
			    u8 *buf_out, u16 *out_size,
			    enum mgmt_direction_type direction,
			    u16 resp_msg_id)
{
	struct hinic_hwif *hwif = pf_to_mgmt->hwif;
	struct pci_dev *pdev = hwif->pdev;
	struct hinic_recv_msg *recv_msg;
	struct completion *recv_done;
	u16 msg_id;
	int err;

	/* Lock the sync_msg_buf */
	down(&pf_to_mgmt->sync_msg_lock);

	recv_msg = &pf_to_mgmt->recv_resp_msg_from_mgmt;
	recv_done = &recv_msg->recv_done;

	if (resp_msg_id == MSG_NOT_RESP)
		msg_id = SYNC_MSG_ID(pf_to_mgmt);
	else
		msg_id = resp_msg_id;

	init_completion(recv_done);

	err = send_msg_to_mgmt(pf_to_mgmt, mod, cmd, buf_in, in_size,
			       MSG_ACK, direction, resp_msg_id);
	if (err) {
		dev_err(&pdev->dev, "Failed to send sync msg to mgmt\n");
		goto unlock_sync_msg;
	}

	if (!wait_for_completion_timeout(recv_done, MGMT_MSG_TIMEOUT)) {
		dev_err(&pdev->dev, "MGMT timeout, MSG id = %d\n", msg_id);
		err = -ETIMEDOUT;
		goto unlock_sync_msg;
	}

	smp_rmb();      /* verify reading after completion */

	if (recv_msg->msg_id != msg_id) {
		dev_err(&pdev->dev, "incorrect MSG for id = %d\n", msg_id);
		err = -EFAULT;
		goto unlock_sync_msg;
	}

	if ((buf_out) && (recv_msg->msg_len <= MAX_PF_MGMT_BUF_SIZE)) {
		memcpy(buf_out, recv_msg->msg, recv_msg->msg_len);
		*out_size = recv_msg->msg_len;
	}

unlock_sync_msg:
	up(&pf_to_mgmt->sync_msg_lock);
	return err;
}