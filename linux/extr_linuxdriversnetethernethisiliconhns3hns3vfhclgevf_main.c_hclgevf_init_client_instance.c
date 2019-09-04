#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hnae3_client {int type; TYPE_1__* ops; } ;
struct hnae3_ae_dev {struct hclgevf_dev* priv; } ;
struct TYPE_7__ {struct hnae3_client* client; } ;
struct hclgevf_dev {TYPE_2__ roce; struct hnae3_client* nic_client; struct hnae3_client* roce_client; TYPE_2__ nic; } ;
struct TYPE_6__ {int (* init_instance ) (TYPE_2__*) ;} ;

/* Variables and functions */
#define  HNAE3_CLIENT_KNIC 130 
#define  HNAE3_CLIENT_ROCE 129 
#define  HNAE3_CLIENT_UNIC 128 
 int hclgevf_init_roce_base_info (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hnae3_dev_roce_supported (struct hclgevf_dev*) ; 
 int stub1 (TYPE_2__*) ; 
 int stub2 (TYPE_2__*) ; 
 int stub3 (TYPE_2__*) ; 
 int stub4 (TYPE_2__*) ; 

__attribute__((used)) static int hclgevf_init_client_instance(struct hnae3_client *client,
					struct hnae3_ae_dev *ae_dev)
{
	struct hclgevf_dev *hdev = ae_dev->priv;
	int ret;

	switch (client->type) {
	case HNAE3_CLIENT_KNIC:
		hdev->nic_client = client;
		hdev->nic.client = client;

		ret = client->ops->init_instance(&hdev->nic);
		if (ret)
			return ret;

		if (hdev->roce_client && hnae3_dev_roce_supported(hdev)) {
			struct hnae3_client *rc = hdev->roce_client;

			ret = hclgevf_init_roce_base_info(hdev);
			if (ret)
				return ret;
			ret = rc->ops->init_instance(&hdev->roce);
			if (ret)
				return ret;
		}
		break;
	case HNAE3_CLIENT_UNIC:
		hdev->nic_client = client;
		hdev->nic.client = client;

		ret = client->ops->init_instance(&hdev->nic);
		if (ret)
			return ret;
		break;
	case HNAE3_CLIENT_ROCE:
		if (hnae3_dev_roce_supported(hdev)) {
			hdev->roce_client = client;
			hdev->roce.client = client;
		}

		if (hdev->roce_client && hdev->nic_client) {
			ret = hclgevf_init_roce_base_info(hdev);
			if (ret)
				return ret;

			ret = client->ops->init_instance(&hdev->roce);
			if (ret)
				return ret;
		}
	}

	return 0;
}