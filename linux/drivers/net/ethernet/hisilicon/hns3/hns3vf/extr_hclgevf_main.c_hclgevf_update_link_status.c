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
struct hnae3_handle {struct hnae3_client* client; } ;
struct hnae3_client {TYPE_1__* ops; } ;
struct TYPE_5__ {int link; } ;
struct TYPE_6__ {TYPE_2__ mac; } ;
struct hclgevf_dev {TYPE_3__ hw; int /*<<< orphan*/  state; struct hnae3_client* roce_client; struct hnae3_handle nic; struct hnae3_handle roce; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* link_status_change ) (struct hnae3_handle*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_STATE_DOWN ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*,int) ; 
 int /*<<< orphan*/  stub2 (struct hnae3_handle*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hclgevf_update_link_status(struct hclgevf_dev *hdev, int link_state)
{
	struct hnae3_handle *rhandle = &hdev->roce;
	struct hnae3_handle *handle = &hdev->nic;
	struct hnae3_client *rclient;
	struct hnae3_client *client;

	client = handle->client;
	rclient = hdev->roce_client;

	link_state =
		test_bit(HCLGEVF_STATE_DOWN, &hdev->state) ? 0 : link_state;

	if (link_state != hdev->hw.mac.link) {
		client->ops->link_status_change(handle, !!link_state);
		if (rclient && rclient->ops->link_status_change)
			rclient->ops->link_status_change(rhandle, !!link_state);
		hdev->hw.mac.link = link_state;
	}
}