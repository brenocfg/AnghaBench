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
struct hclge_mbx_vf_to_pf_cmd {int /*<<< orphan*/ * msg; } ;
struct hclge_dev {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_SERVICE_SCHED ; 
 size_t LINK_FAIL_CODE_OFFSET ; 
 size_t LINK_STATUS_OFFSET ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hclge_link_fail_parse (struct hclge_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_task_schedule (struct hclge_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_handle_link_change_event(struct hclge_dev *hdev,
					   struct hclge_mbx_vf_to_pf_cmd *req)
{
#define LINK_STATUS_OFFSET	1
#define LINK_FAIL_CODE_OFFSET	2

	clear_bit(HCLGE_STATE_SERVICE_SCHED, &hdev->state);
	hclge_task_schedule(hdev, 0);

	if (!req->msg[LINK_STATUS_OFFSET])
		hclge_link_fail_parse(hdev, req->msg[LINK_FAIL_CODE_OFFSET]);
}