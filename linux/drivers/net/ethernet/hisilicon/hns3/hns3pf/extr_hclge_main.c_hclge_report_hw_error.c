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
typedef  size_t u16 ;
struct hnae3_client {TYPE_2__* ops; } ;
struct hclge_dev {size_t num_vmdq_vport; TYPE_1__* vport; int /*<<< orphan*/  state; struct hnae3_client* nic_client; } ;
typedef  enum hnae3_hw_error_type { ____Placeholder_hnae3_hw_error_type } hnae3_hw_error_type ;
struct TYPE_4__ {int /*<<< orphan*/  (* process_hw_error ) (int /*<<< orphan*/ *,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  nic; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_NIC_REGISTERED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hclge_report_hw_error(struct hclge_dev *hdev,
			   enum hnae3_hw_error_type type)
{
	struct hnae3_client *client = hdev->nic_client;
	u16 i;

	if (!client || !client->ops->process_hw_error ||
	    !test_bit(HCLGE_STATE_NIC_REGISTERED, &hdev->state))
		return;

	for (i = 0; i < hdev->num_vmdq_vport + 1; i++)
		client->ops->process_hw_error(&hdev->vport[i].nic, type);
}