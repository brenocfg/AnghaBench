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
typedef  size_t u16 ;
struct hnae3_handle {int dummy; } ;
struct hnae3_client {TYPE_2__* ops; } ;
struct hclge_dev {size_t num_vmdq_vport; TYPE_3__* pdev; TYPE_1__* vport; int /*<<< orphan*/  state; struct hnae3_client* nic_client; } ;
typedef  enum hnae3_reset_notify_type { ____Placeholder_hnae3_reset_notify_type } hnae3_reset_notify_type ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int (* reset_notify ) (struct hnae3_handle*,int) ;} ;
struct TYPE_4__ {struct hnae3_handle nic; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HCLGE_STATE_NIC_REGISTERED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int stub1 (struct hnae3_handle*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hclge_notify_client(struct hclge_dev *hdev,
			enum hnae3_reset_notify_type type)
{
	struct hnae3_client *client = hdev->nic_client;
	u16 i;

	if (!test_bit(HCLGE_STATE_NIC_REGISTERED, &hdev->state) || !client)
		return 0;

	if (!client->ops->reset_notify)
		return -EOPNOTSUPP;

	for (i = 0; i < hdev->num_vmdq_vport + 1; i++) {
		struct hnae3_handle *handle = &hdev->vport[i].nic;
		int ret;

		ret = client->ops->reset_notify(handle, type);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"notify nic client failed %d(%d)\n", type, ret);
			return ret;
		}
	}

	return 0;
}