#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_tqps; int /*<<< orphan*/ * tqp; } ;
struct hnae3_handle {TYPE_2__ kinfo; } ;
struct hclgevf_dev {int /*<<< orphan*/  service_timer; int /*<<< orphan*/  state; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_STATE_DOWN ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_get_queue_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclgevf_request_link_info (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_reset_tqp_stats (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclgevf_tqp_enable (struct hclgevf_dev*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int hclgevf_ae_start(struct hnae3_handle *handle)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	int i, queue_id;

	for (i = 0; i < handle->kinfo.num_tqps; i++) {
		/* ring enable */
		queue_id = hclgevf_get_queue_id(handle->kinfo.tqp[i]);
		if (queue_id < 0) {
			dev_warn(&hdev->pdev->dev,
				 "Get invalid queue id, ignore it\n");
			continue;
		}

		hclgevf_tqp_enable(hdev, queue_id, 0, true);
	}

	/* reset tqp stats */
	hclgevf_reset_tqp_stats(handle);

	hclgevf_request_link_info(hdev);

	clear_bit(HCLGEVF_STATE_DOWN, &hdev->state);
	mod_timer(&hdev->service_timer, jiffies + HZ);

	return 0;
}