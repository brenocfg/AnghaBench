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
struct hnae3_handle {int dummy; } ;
struct hnae3_client {TYPE_1__* ops; } ;
struct hclge_dev {size_t num_vmdq_vport; TYPE_2__* vport; struct hnae3_client* nic_client; } ;
typedef  enum hnae3_reset_notify_type { ____Placeholder_hnae3_reset_notify_type } hnae3_reset_notify_type ;
struct TYPE_4__ {struct hnae3_handle nic; } ;
struct TYPE_3__ {int (* reset_notify ) (struct hnae3_handle*,int) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct hnae3_handle*,int) ; 

__attribute__((used)) static int hclge_notify_client(struct hclge_dev *hdev,
			       enum hnae3_reset_notify_type type)
{
	struct hnae3_client *client = hdev->nic_client;
	u16 i;

	if (!client->ops->reset_notify)
		return -EOPNOTSUPP;

	for (i = 0; i < hdev->num_vmdq_vport + 1; i++) {
		struct hnae3_handle *handle = &hdev->vport[i].nic;
		int ret;

		ret = client->ops->reset_notify(handle, type);
		if (ret)
			return ret;
	}

	return 0;
}