#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hnae3_client {scalar_t__ type; TYPE_3__* ops; } ;
struct hnae3_ae_dev {struct hclge_dev* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/ * client; } ;
struct TYPE_10__ {int /*<<< orphan*/ * client; } ;
struct hclge_vport {TYPE_4__ nic; TYPE_5__ roce; } ;
struct hclge_dev {int num_vmdq_vport; int /*<<< orphan*/ * nic_client; int /*<<< orphan*/  state; TYPE_2__* roce_client; struct hclge_vport* vport; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* uninit_instance ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* uninit_instance ) (TYPE_5__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_NIC_REGISTERED ; 
 int /*<<< orphan*/  HCLGE_STATE_ROCE_REGISTERED ; 
 int /*<<< orphan*/  HCLGE_STATE_RST_HANDLING ; 
 int /*<<< orphan*/  HCLGE_WAIT_RESET_DONE ; 
 scalar_t__ HNAE3_CLIENT_ROCE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_uninit_client_instance(struct hnae3_client *client,
					 struct hnae3_ae_dev *ae_dev)
{
	struct hclge_dev *hdev = ae_dev->priv;
	struct hclge_vport *vport;
	int i;

	for (i = 0; i < hdev->num_vmdq_vport + 1; i++) {
		vport = &hdev->vport[i];
		if (hdev->roce_client) {
			clear_bit(HCLGE_STATE_ROCE_REGISTERED, &hdev->state);
			while (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state))
				msleep(HCLGE_WAIT_RESET_DONE);

			hdev->roce_client->ops->uninit_instance(&vport->roce,
								0);
			hdev->roce_client = NULL;
			vport->roce.client = NULL;
		}
		if (client->type == HNAE3_CLIENT_ROCE)
			return;
		if (hdev->nic_client && client->ops->uninit_instance) {
			clear_bit(HCLGE_STATE_NIC_REGISTERED, &hdev->state);
			while (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state))
				msleep(HCLGE_WAIT_RESET_DONE);

			client->ops->uninit_instance(&vport->nic, 0);
			hdev->nic_client = NULL;
			vport->nic.client = NULL;
		}
	}
}