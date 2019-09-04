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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int next_to_use; int desc_num; int /*<<< orphan*/  lock; struct hclgevf_desc* desc; } ;
struct TYPE_5__ {scalar_t__ tx_timeout; int last_status; TYPE_3__ csq; } ;
struct hclgevf_hw {TYPE_2__ cmq; scalar_t__ hdev; } ;
struct hclgevf_dev {TYPE_1__* pdev; } ;
struct hclgevf_desc {int /*<<< orphan*/  retval; int /*<<< orphan*/  flag; int /*<<< orphan*/  opcode; } ;
typedef  enum hclgevf_cmd_status { ____Placeholder_hclgevf_cmd_status } hclgevf_cmd_status ;
typedef  enum hclgevf_cmd_return_status { ____Placeholder_hclgevf_cmd_return_status } hclgevf_cmd_return_status ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EIO ; 
 int HCLGEVF_CMD_EXEC_SUCCESS ; 
 int /*<<< orphan*/  HCLGEVF_NIC_CSQ_TAIL_REG ; 
 scalar_t__ HCLGEVF_SEND_SYNC (scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int hclgevf_cmd_csq_clean (struct hclgevf_hw*) ; 
 scalar_t__ hclgevf_cmd_csq_done (struct hclgevf_hw*) ; 
 int /*<<< orphan*/  hclgevf_is_special_opcode (scalar_t__) ; 
 int hclgevf_ring_space (TYPE_3__*) ; 
 int /*<<< orphan*/  hclgevf_write_dev (struct hclgevf_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

int hclgevf_cmd_send(struct hclgevf_hw *hw, struct hclgevf_desc *desc, int num)
{
	struct hclgevf_dev *hdev = (struct hclgevf_dev *)hw->hdev;
	struct hclgevf_desc *desc_to_use;
	bool complete = false;
	u32 timeout = 0;
	int handle = 0;
	int status = 0;
	u16 retval;
	u16 opcode;
	int ntc;

	spin_lock_bh(&hw->cmq.csq.lock);

	if (num > hclgevf_ring_space(&hw->cmq.csq)) {
		spin_unlock_bh(&hw->cmq.csq.lock);
		return -EBUSY;
	}

	/* Record the location of desc in the ring for this time
	 * which will be use for hardware to write back
	 */
	ntc = hw->cmq.csq.next_to_use;
	opcode = le16_to_cpu(desc[0].opcode);
	while (handle < num) {
		desc_to_use = &hw->cmq.csq.desc[hw->cmq.csq.next_to_use];
		*desc_to_use = desc[handle];
		(hw->cmq.csq.next_to_use)++;
		if (hw->cmq.csq.next_to_use == hw->cmq.csq.desc_num)
			hw->cmq.csq.next_to_use = 0;
		handle++;
	}

	/* Write to hardware */
	hclgevf_write_dev(hw, HCLGEVF_NIC_CSQ_TAIL_REG,
			  hw->cmq.csq.next_to_use);

	/* If the command is sync, wait for the firmware to write back,
	 * if multi descriptors to be sent, use the first one to check
	 */
	if (HCLGEVF_SEND_SYNC(le16_to_cpu(desc->flag))) {
		do {
			if (hclgevf_cmd_csq_done(hw))
				break;
			udelay(1);
			timeout++;
		} while (timeout < hw->cmq.tx_timeout);
	}

	if (hclgevf_cmd_csq_done(hw)) {
		complete = true;
		handle = 0;

		while (handle < num) {
			/* Get the result of hardware write back */
			desc_to_use = &hw->cmq.csq.desc[ntc];
			desc[handle] = *desc_to_use;

			if (likely(!hclgevf_is_special_opcode(opcode)))
				retval = le16_to_cpu(desc[handle].retval);
			else
				retval = le16_to_cpu(desc[0].retval);

			if ((enum hclgevf_cmd_return_status)retval ==
			    HCLGEVF_CMD_EXEC_SUCCESS)
				status = 0;
			else
				status = -EIO;
			hw->cmq.last_status = (enum hclgevf_cmd_status)retval;
			ntc++;
			handle++;
			if (ntc == hw->cmq.csq.desc_num)
				ntc = 0;
		}
	}

	if (!complete)
		status = -EAGAIN;

	/* Clean the command send queue */
	handle = hclgevf_cmd_csq_clean(hw);
	if (handle != num) {
		dev_warn(&hdev->pdev->dev,
			 "cleaned %d, need to clean %d\n", handle, num);
	}

	spin_unlock_bh(&hw->cmq.csq.lock);

	return status;
}