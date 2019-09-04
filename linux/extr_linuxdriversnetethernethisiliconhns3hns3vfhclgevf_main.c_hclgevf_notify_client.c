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
struct hnae3_handle {int dummy; } ;
struct hnae3_client {TYPE_1__* ops; } ;
struct hclgevf_dev {struct hnae3_handle nic; struct hnae3_client* nic_client; } ;
typedef  enum hnae3_reset_notify_type { ____Placeholder_hnae3_reset_notify_type } hnae3_reset_notify_type ;
struct TYPE_2__ {int (* reset_notify ) (struct hnae3_handle*,int) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct hnae3_handle*,int) ; 

__attribute__((used)) static int hclgevf_notify_client(struct hclgevf_dev *hdev,
				 enum hnae3_reset_notify_type type)
{
	struct hnae3_client *client = hdev->nic_client;
	struct hnae3_handle *handle = &hdev->nic;

	if (!client->ops->reset_notify)
		return -EOPNOTSUPP;

	return client->ops->reset_notify(handle, type);
}