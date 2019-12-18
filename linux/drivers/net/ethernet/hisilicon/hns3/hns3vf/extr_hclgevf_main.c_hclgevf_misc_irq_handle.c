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
typedef  int /*<<< orphan*/  u32 ;
struct hclgevf_dev {int /*<<< orphan*/  misc_vector; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum hclgevf_evt_cause { ____Placeholder_hclgevf_evt_cause } hclgevf_evt_cause ;

/* Variables and functions */
#define  HCLGEVF_VECTOR0_EVENT_MBX 129 
 int HCLGEVF_VECTOR0_EVENT_OTHER ; 
#define  HCLGEVF_VECTOR0_EVENT_RST 128 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int hclgevf_check_evt_cause (struct hclgevf_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hclgevf_clear_event_cause (struct hclgevf_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclgevf_enable_vector (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hclgevf_mbx_handler (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_reset_task_schedule (struct hclgevf_dev*) ; 

__attribute__((used)) static irqreturn_t hclgevf_misc_irq_handle(int irq, void *data)
{
	enum hclgevf_evt_cause event_cause;
	struct hclgevf_dev *hdev = data;
	u32 clearval;

	hclgevf_enable_vector(&hdev->misc_vector, false);
	event_cause = hclgevf_check_evt_cause(hdev, &clearval);

	switch (event_cause) {
	case HCLGEVF_VECTOR0_EVENT_RST:
		hclgevf_reset_task_schedule(hdev);
		break;
	case HCLGEVF_VECTOR0_EVENT_MBX:
		hclgevf_mbx_handler(hdev);
		break;
	default:
		break;
	}

	if (event_cause != HCLGEVF_VECTOR0_EVENT_OTHER) {
		hclgevf_clear_event_cause(hdev, clearval);
		hclgevf_enable_vector(&hdev->misc_vector, true);
	}

	return IRQ_HANDLED;
}