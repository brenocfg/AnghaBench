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
struct hnae3_handle {int dummy; } ;
struct hclgevf_dev {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_STATE_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclgevf_request_link_info (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_reset_tqp_stats (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclgevf_update_link_mode (struct hclgevf_dev*) ; 

__attribute__((used)) static int hclgevf_ae_start(struct hnae3_handle *handle)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	hclgevf_reset_tqp_stats(handle);

	hclgevf_request_link_info(hdev);

	hclgevf_update_link_mode(hdev);

	clear_bit(HCLGEVF_STATE_DOWN, &hdev->state);

	return 0;
}