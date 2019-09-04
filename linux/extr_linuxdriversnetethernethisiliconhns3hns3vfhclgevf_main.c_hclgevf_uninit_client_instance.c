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
struct hnae3_client {scalar_t__ type; TYPE_3__* ops; } ;
struct hnae3_ae_dev {struct hclgevf_dev* priv; } ;
struct hclgevf_dev {int /*<<< orphan*/  nic; int /*<<< orphan*/  roce; TYPE_2__* roce_client; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* uninit_instance ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* uninit_instance ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ HNAE3_CLIENT_ROCE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclgevf_uninit_client_instance(struct hnae3_client *client,
					   struct hnae3_ae_dev *ae_dev)
{
	struct hclgevf_dev *hdev = ae_dev->priv;

	/* un-init roce, if it exists */
	if (hdev->roce_client)
		hdev->roce_client->ops->uninit_instance(&hdev->roce, 0);

	/* un-init nic/unic, if this was not called by roce client */
	if ((client->ops->uninit_instance) &&
	    (client->type != HNAE3_CLIENT_ROCE))
		client->ops->uninit_instance(&hdev->nic, 0);
}