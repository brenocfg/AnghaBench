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
struct hnae3_handle {int /*<<< orphan*/  last_reset_time; int /*<<< orphan*/  reset_level; } ;
struct hclgevf_dev {int /*<<< orphan*/  reset_state; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_RESET_REQUESTED ; 
 int /*<<< orphan*/  HNAE3_VF_RESET ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclgevf_reset_task_schedule (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclgevf_reset_event(struct hnae3_handle *handle)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	dev_info(&hdev->pdev->dev, "received reset request from VF enet\n");

	handle->reset_level = HNAE3_VF_RESET;

	/* reset of this VF requested */
	set_bit(HCLGEVF_RESET_REQUESTED, &hdev->reset_state);
	hclgevf_reset_task_schedule(hdev);

	handle->last_reset_time = jiffies;
}