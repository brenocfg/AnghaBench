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
struct hnae3_ae_dev {struct hclgevf_dev* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/ * client; } ;
struct TYPE_10__ {int /*<<< orphan*/ * client; } ;
struct hclgevf_dev {TYPE_4__ nic; int /*<<< orphan*/ * nic_client; int /*<<< orphan*/  state; TYPE_5__ roce; TYPE_2__* roce_client; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* uninit_instance ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* uninit_instance ) (TYPE_5__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_STATE_NIC_REGISTERED ; 
 scalar_t__ HNAE3_CLIENT_ROCE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclgevf_uninit_client_instance(struct hnae3_client *client,
					   struct hnae3_ae_dev *ae_dev)
{
	struct hclgevf_dev *hdev = ae_dev->priv;

	/* un-init roce, if it exists */
	if (hdev->roce_client) {
		hdev->roce_client->ops->uninit_instance(&hdev->roce, 0);
		hdev->roce_client = NULL;
		hdev->roce.client = NULL;
	}

	/* un-init nic/unic, if this was not called by roce client */
	if (client->ops->uninit_instance && hdev->nic_client &&
	    client->type != HNAE3_CLIENT_ROCE) {
		clear_bit(HCLGEVF_STATE_NIC_REGISTERED, &hdev->state);

		client->ops->uninit_instance(&hdev->nic, 0);
		hdev->nic_client = NULL;
		hdev->nic.client = NULL;
	}
}