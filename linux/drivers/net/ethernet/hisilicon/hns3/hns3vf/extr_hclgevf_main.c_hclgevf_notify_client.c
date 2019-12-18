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
struct hnae3_handle {int dummy; } ;
struct hnae3_client {TYPE_2__* ops; } ;
struct hclgevf_dev {TYPE_1__* pdev; int /*<<< orphan*/  state; struct hnae3_handle nic; struct hnae3_client* nic_client; } ;
typedef  enum hnae3_reset_notify_type { ____Placeholder_hnae3_reset_notify_type } hnae3_reset_notify_type ;
struct TYPE_4__ {int (* reset_notify ) (struct hnae3_handle*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HCLGEVF_STATE_NIC_REGISTERED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int stub1 (struct hnae3_handle*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclgevf_notify_client(struct hclgevf_dev *hdev,
				 enum hnae3_reset_notify_type type)
{
	struct hnae3_client *client = hdev->nic_client;
	struct hnae3_handle *handle = &hdev->nic;
	int ret;

	if (!test_bit(HCLGEVF_STATE_NIC_REGISTERED, &hdev->state) ||
	    !client)
		return 0;

	if (!client->ops->reset_notify)
		return -EOPNOTSUPP;

	ret = client->ops->reset_notify(handle, type);
	if (ret)
		dev_err(&hdev->pdev->dev, "notify nic client failed %d(%d)\n",
			type, ret);

	return ret;
}