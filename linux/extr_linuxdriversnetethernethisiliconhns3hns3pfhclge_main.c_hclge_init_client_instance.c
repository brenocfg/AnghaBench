#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct hnae3_client {int type; TYPE_1__* ops; } ;
struct hnae3_ae_dev {struct hclge_dev* priv; } ;
struct TYPE_8__ {struct hnae3_client* client; } ;
struct hclge_vport {TYPE_2__ roce; TYPE_2__ nic; } ;
struct hclge_dev {int num_vmdq_vport; struct hnae3_client* nic_client; struct hnae3_client* roce_client; struct hclge_vport* vport; } ;
struct TYPE_7__ {int (* init_instance ) (TYPE_2__*) ;int /*<<< orphan*/  (* uninit_instance ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  HNAE3_CLIENT_KNIC 130 
#define  HNAE3_CLIENT_ROCE 129 
#define  HNAE3_CLIENT_UNIC 128 
 int hclge_init_instance_hw (struct hclge_dev*) ; 
 int hclge_init_roce_base_info (struct hclge_vport*) ; 
 int /*<<< orphan*/  hnae3_dev_roce_supported (struct hclge_dev*) ; 
 int stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int stub3 (TYPE_2__*) ; 
 int stub4 (TYPE_2__*) ; 
 int stub5 (TYPE_2__*) ; 

__attribute__((used)) static int hclge_init_client_instance(struct hnae3_client *client,
				      struct hnae3_ae_dev *ae_dev)
{
	struct hclge_dev *hdev = ae_dev->priv;
	struct hclge_vport *vport;
	int i, ret;

	for (i = 0; i <  hdev->num_vmdq_vport + 1; i++) {
		vport = &hdev->vport[i];

		switch (client->type) {
		case HNAE3_CLIENT_KNIC:

			hdev->nic_client = client;
			vport->nic.client = client;
			ret = client->ops->init_instance(&vport->nic);
			if (ret)
				return ret;

			ret = hclge_init_instance_hw(hdev);
			if (ret) {
			        client->ops->uninit_instance(&vport->nic,
			                                     0);
			        return ret;
			}

			if (hdev->roce_client &&
			    hnae3_dev_roce_supported(hdev)) {
				struct hnae3_client *rc = hdev->roce_client;

				ret = hclge_init_roce_base_info(vport);
				if (ret)
					return ret;

				ret = rc->ops->init_instance(&vport->roce);
				if (ret)
					return ret;
			}

			break;
		case HNAE3_CLIENT_UNIC:
			hdev->nic_client = client;
			vport->nic.client = client;

			ret = client->ops->init_instance(&vport->nic);
			if (ret)
				return ret;

			break;
		case HNAE3_CLIENT_ROCE:
			if (hnae3_dev_roce_supported(hdev)) {
				hdev->roce_client = client;
				vport->roce.client = client;
			}

			if (hdev->roce_client && hdev->nic_client) {
				ret = hclge_init_roce_base_info(vport);
				if (ret)
					return ret;

				ret = client->ops->init_instance(&vport->roce);
				if (ret)
					return ret;
			}
		}
	}

	return 0;
}