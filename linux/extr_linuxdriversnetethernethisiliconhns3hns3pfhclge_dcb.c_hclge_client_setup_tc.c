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
typedef  size_t u32 ;
struct hnae3_handle {struct hnae3_client* client; } ;
struct hnae3_client {TYPE_1__* ops; } ;
struct hclge_vport {struct hnae3_handle nic; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_tc; } ;
struct hclge_dev {size_t num_vmdq_vport; TYPE_2__ tm_info; struct hclge_vport* vport; } ;
struct TYPE_3__ {int (* setup_tc ) (struct hnae3_handle*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct hnae3_handle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_client_setup_tc(struct hclge_dev *hdev)
{
	struct hclge_vport *vport = hdev->vport;
	struct hnae3_client *client;
	struct hnae3_handle *handle;
	int ret;
	u32 i;

	for (i = 0; i < hdev->num_vmdq_vport + 1; i++) {
		handle = &vport[i].nic;
		client = handle->client;

		if (!client || !client->ops || !client->ops->setup_tc)
			continue;

		ret = client->ops->setup_tc(handle, hdev->tm_info.num_tc);
		if (ret)
			return ret;
	}

	return 0;
}