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

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  hclgevf_check_event_cause (struct hclgevf_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hclgevf_clear_event_cause (struct hclgevf_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclgevf_enable_vector (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hclgevf_mbx_handler (struct hclgevf_dev*) ; 

__attribute__((used)) static irqreturn_t hclgevf_misc_irq_handle(int irq, void *data)
{
	struct hclgevf_dev *hdev = data;
	u32 clearval;

	hclgevf_enable_vector(&hdev->misc_vector, false);
	if (!hclgevf_check_event_cause(hdev, &clearval))
		goto skip_sched;

	hclgevf_mbx_handler(hdev);

	hclgevf_clear_event_cause(hdev, clearval);

skip_sched:
	hclgevf_enable_vector(&hdev->misc_vector, true);

	return IRQ_HANDLED;
}