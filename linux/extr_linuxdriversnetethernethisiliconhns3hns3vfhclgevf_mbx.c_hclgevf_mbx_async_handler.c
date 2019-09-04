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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct TYPE_6__ {size_t tail; size_t head; int** msg_q; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {int /*<<< orphan*/  reset_level; } ;
struct hclgevf_dev {int mbx_event_pending; TYPE_3__ arq; TYPE_2__* pdev; int /*<<< orphan*/  reset_state; TYPE_1__ nic; } ;
typedef  int /*<<< orphan*/  speed ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_RESET_PENDING ; 
#define  HCLGE_MBX_ASSERTING_RESET 129 
#define  HCLGE_MBX_LINK_STAT_CHANGE 128 
 int /*<<< orphan*/  HNAE3_VF_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hclge_mbx_head_ptr_move_arq (TYPE_3__) ; 
 int /*<<< orphan*/  hclgevf_reset_task_schedule (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_update_link_status (struct hclgevf_dev*,int) ; 
 int /*<<< orphan*/  hclgevf_update_speed_duplex (struct hclgevf_dev*,size_t,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  memcpy (size_t*,int*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hclgevf_mbx_async_handler(struct hclgevf_dev *hdev)
{
	u16 link_status;
	u16 *msg_q;
	u8 duplex;
	u32 speed;
	u32 tail;

	/* we can safely clear it now as we are at start of the async message
	 * processing
	 */
	hdev->mbx_event_pending = false;

	tail = hdev->arq.tail;

	/* process all the async queue messages */
	while (tail != hdev->arq.head) {
		msg_q = hdev->arq.msg_q[hdev->arq.head];

		switch (msg_q[0]) {
		case HCLGE_MBX_LINK_STAT_CHANGE:
			link_status = le16_to_cpu(msg_q[1]);
			memcpy(&speed, &msg_q[2], sizeof(speed));
			duplex = (u8)le16_to_cpu(msg_q[4]);

			/* update upper layer with new link link status */
			hclgevf_update_link_status(hdev, link_status);
			hclgevf_update_speed_duplex(hdev, speed, duplex);

			break;
		case HCLGE_MBX_ASSERTING_RESET:
			/* PF has asserted reset hence VF should go in pending
			 * state and poll for the hardware reset status till it
			 * has been completely reset. After this stack should
			 * eventually be re-initialized.
			 */
			hdev->nic.reset_level = HNAE3_VF_RESET;
			set_bit(HCLGEVF_RESET_PENDING, &hdev->reset_state);
			hclgevf_reset_task_schedule(hdev);

			break;
		default:
			dev_err(&hdev->pdev->dev,
				"fetched unsupported(%d) message from arq\n",
				msg_q[0]);
			break;
		}

		hclge_mbx_head_ptr_move_arq(hdev->arq);
		hdev->arq.count--;
		msg_q = hdev->arq.msg_q[hdev->arq.head];
	}
}