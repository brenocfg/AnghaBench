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
struct hnae3_client {int type; } ;
struct hnae3_ae_dev {struct hclgevf_dev* priv; } ;
struct TYPE_4__ {struct hnae3_client* client; } ;
struct TYPE_3__ {struct hnae3_client* client; } ;
struct hclgevf_dev {TYPE_2__ roce; struct hnae3_client* roce_client; TYPE_1__ nic; struct hnae3_client* nic_client; } ;

/* Variables and functions */
 int EINVAL ; 
#define  HNAE3_CLIENT_KNIC 129 
#define  HNAE3_CLIENT_ROCE 128 
 int hclgevf_init_nic_client_instance (struct hnae3_ae_dev*,struct hnae3_client*) ; 
 int hclgevf_init_roce_client_instance (struct hnae3_ae_dev*,struct hnae3_client*) ; 
 int /*<<< orphan*/  hnae3_dev_roce_supported (struct hclgevf_dev*) ; 

__attribute__((used)) static int hclgevf_init_client_instance(struct hnae3_client *client,
					struct hnae3_ae_dev *ae_dev)
{
	struct hclgevf_dev *hdev = ae_dev->priv;
	int ret;

	switch (client->type) {
	case HNAE3_CLIENT_KNIC:
		hdev->nic_client = client;
		hdev->nic.client = client;

		ret = hclgevf_init_nic_client_instance(ae_dev, client);
		if (ret)
			goto clear_nic;

		ret = hclgevf_init_roce_client_instance(ae_dev,
							hdev->roce_client);
		if (ret)
			goto clear_roce;

		break;
	case HNAE3_CLIENT_ROCE:
		if (hnae3_dev_roce_supported(hdev)) {
			hdev->roce_client = client;
			hdev->roce.client = client;
		}

		ret = hclgevf_init_roce_client_instance(ae_dev, client);
		if (ret)
			goto clear_roce;

		break;
	default:
		return -EINVAL;
	}

	return 0;

clear_nic:
	hdev->nic_client = NULL;
	hdev->nic.client = NULL;
	return ret;
clear_roce:
	hdev->roce_client = NULL;
	hdev->roce.client = NULL;
	return ret;
}