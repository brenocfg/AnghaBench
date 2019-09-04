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
struct i40evf_adapter {scalar_t__ state; TYPE_1__* pdev; } ;
struct i40e_client_instance {int /*<<< orphan*/  state; int /*<<< orphan*/  lan_info; } ;
struct i40e_client {TYPE_2__* ops; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int (* open ) (int /*<<< orphan*/ *,struct i40e_client*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ __I40EVF_DOWN ; 
 int /*<<< orphan*/  __I40E_CLIENT_INSTANCE_OPENED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct i40e_client_instance* i40evf_client_add_instance (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_client_del_instance (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,struct i40e_client*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct i40e_client* vf_registered_client ; 

void i40evf_client_subtask(struct i40evf_adapter *adapter)
{
	struct i40e_client *client = vf_registered_client;
	struct i40e_client_instance *cinst;
	int ret = 0;

	if (adapter->state < __I40EVF_DOWN)
		return;

	/* first check client is registered */
	if (!client)
		return;

	/* Add the client instance to the instance list */
	cinst = i40evf_client_add_instance(adapter);
	if (!cinst)
		return;

	dev_info(&adapter->pdev->dev, "Added instance of Client %s\n",
		 client->name);

	if (!test_bit(__I40E_CLIENT_INSTANCE_OPENED, &cinst->state)) {
		/* Send an Open request to the client */

		if (client->ops && client->ops->open)
			ret = client->ops->open(&cinst->lan_info, client);
		if (!ret)
			set_bit(__I40E_CLIENT_INSTANCE_OPENED,
				&cinst->state);
		else
			/* remove client instance */
			i40evf_client_del_instance(adapter);
	}
}