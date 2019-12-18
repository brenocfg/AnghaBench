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
struct hclge_dev {int /*<<< orphan*/  misc_vector; TYPE_1__* pdev; int /*<<< orphan*/  reset_request; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  HCLGE_VECTOR0_EVENT_ERR 130 
#define  HCLGE_VECTOR0_EVENT_MBX 129 
#define  HCLGE_VECTOR0_EVENT_RST 128 
 int /*<<< orphan*/  HNAE3_UNKNOWN_RESET ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int hclge_check_event_cause (struct hclge_dev*,int*) ; 
 int /*<<< orphan*/  hclge_clear_event_cause (struct hclge_dev*,int,int) ; 
 int /*<<< orphan*/  hclge_enable_vector (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hclge_mbx_task_schedule (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_reset_task_schedule (struct hclge_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t hclge_misc_irq_handle(int irq, void *data)
{
	struct hclge_dev *hdev = data;
	u32 clearval = 0;
	u32 event_cause;

	hclge_enable_vector(&hdev->misc_vector, false);
	event_cause = hclge_check_event_cause(hdev, &clearval);

	/* vector 0 interrupt is shared with reset and mailbox source events.*/
	switch (event_cause) {
	case HCLGE_VECTOR0_EVENT_ERR:
		/* we do not know what type of reset is required now. This could
		 * only be decided after we fetch the type of errors which
		 * caused this event. Therefore, we will do below for now:
		 * 1. Assert HNAE3_UNKNOWN_RESET type of reset. This means we
		 *    have defered type of reset to be used.
		 * 2. Schedule the reset serivce task.
		 * 3. When service task receives  HNAE3_UNKNOWN_RESET type it
		 *    will fetch the correct type of reset.  This would be done
		 *    by first decoding the types of errors.
		 */
		set_bit(HNAE3_UNKNOWN_RESET, &hdev->reset_request);
		/* fall through */
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

	hclge_clear_event_cause(hdev, event_cause, clearval);

	/* Enable interrupt if it is not cause by reset. And when
	 * clearval equal to 0, it means interrupt status may be
	 * cleared by hardware before driver reads status register.
	 * For this case, vector0 interrupt also should be enabled.
	 */
	if (!clearval ||
	    event_cause == HCLGE_VECTOR0_EVENT_MBX) {
		hclge_enable_vector(&hdev->misc_vector, true);
	}

	return IRQ_HANDLED;
}