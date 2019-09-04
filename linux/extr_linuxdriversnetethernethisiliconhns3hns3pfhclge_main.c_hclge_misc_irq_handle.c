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
typedef  int u32 ;
struct hclge_dev {int /*<<< orphan*/  misc_vector; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  HCLGE_VECTOR0_EVENT_MBX 129 
#define  HCLGE_VECTOR0_EVENT_RST 128 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int hclge_check_event_cause (struct hclge_dev*,int*) ; 
 int /*<<< orphan*/  hclge_clear_event_cause (struct hclge_dev*,int,int) ; 
 int /*<<< orphan*/  hclge_enable_vector (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hclge_mbx_task_schedule (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_reset_task_schedule (struct hclge_dev*) ; 

__attribute__((used)) static irqreturn_t hclge_misc_irq_handle(int irq, void *data)
{
	struct hclge_dev *hdev = data;
	u32 event_cause;
	u32 clearval;

	hclge_enable_vector(&hdev->misc_vector, false);
	event_cause = hclge_check_event_cause(hdev, &clearval);

	/* vector 0 interrupt is shared with reset and mailbox source events.*/
	switch (event_cause) {
	case HCLGE_VECTOR0_EVENT_RST:
		hclge_reset_task_schedule(hdev);
		break;
	case HCLGE_VECTOR0_EVENT_MBX:
		/* If we are here then,
		 * 1. Either we are not handling any mbx task and we are not
		 *    scheduled as well
		 *                        OR
		 * 2. We could be handling a mbx task but nothing more is
		 *    scheduled.
		 * In both cases, we should schedule mbx task as there are more
		 * mbx messages reported by this interrupt.
		 */
		hclge_mbx_task_schedule(hdev);
		break;
	default:
		dev_warn(&hdev->pdev->dev,
			 "received unknown or unhandled event of vector0\n");
		break;
	}

	/* clear the source of interrupt if it is not cause by reset */
	if (event_cause != HCLGE_VECTOR0_EVENT_RST) {
		hclge_clear_event_cause(hdev, event_cause, clearval);
		hclge_enable_vector(&hdev->misc_vector, true);
	}

	return IRQ_HANDLED;
}