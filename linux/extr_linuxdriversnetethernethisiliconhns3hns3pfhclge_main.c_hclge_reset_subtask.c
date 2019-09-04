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
struct hclge_dev {scalar_t__ reset_type; int /*<<< orphan*/  reset_request; int /*<<< orphan*/  reset_pending; } ;

/* Variables and functions */
 scalar_t__ HNAE3_NONE_RESET ; 
 int /*<<< orphan*/  hclge_do_reset (struct hclge_dev*) ; 
 void* hclge_get_reset_level (struct hclge_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hclge_reset (struct hclge_dev*) ; 

__attribute__((used)) static void hclge_reset_subtask(struct hclge_dev *hdev)
{
	/* check if there is any ongoing reset in the hardware. This status can
	 * be checked from reset_pending. If there is then, we need to wait for
	 * hardware to complete reset.
	 *    a. If we are able to figure out in reasonable time that hardware
	 *       has fully resetted then, we can proceed with driver, client
	 *       reset.
	 *    b. else, we can come back later to check this status so re-sched
	 *       now.
	 */
	hdev->reset_type = hclge_get_reset_level(hdev, &hdev->reset_pending);
	if (hdev->reset_type != HNAE3_NONE_RESET)
		hclge_reset(hdev);

	/* check if we got any *new* reset requests to be honored */
	hdev->reset_type = hclge_get_reset_level(hdev, &hdev->reset_request);
	if (hdev->reset_type != HNAE3_NONE_RESET)
		hclge_do_reset(hdev);

	hdev->reset_type = HNAE3_NONE_RESET;
}