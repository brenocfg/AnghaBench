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
struct i40e_vsi {int /*<<< orphan*/ * state; scalar_t__ netdev_registered; } ;
struct i40e_pf {size_t lan_vsi; int /*<<< orphan*/ * state; struct i40e_client_instance* cinst; struct i40e_vsi** vsi; } ;
struct i40e_client_instance {int /*<<< orphan*/  lan_info; int /*<<< orphan*/  state; } ;
struct i40e_client {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* open ) (int /*<<< orphan*/ *,struct i40e_client*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_CLIENT_VSI_FLAG_TCP_ENABLE ; 
 int /*<<< orphan*/  __I40E_CLIENT_INSTANCE_OPENED ; 
 int /*<<< orphan*/  __I40E_CLIENT_SERVICE_REQUESTED ; 
 int /*<<< orphan*/  __I40E_CONFIG_BUSY ; 
 int /*<<< orphan*/  __I40E_DOWN ; 
 int /*<<< orphan*/  __I40E_VSI_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_client_del_instance (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_client_update_vsi_ctxt (int /*<<< orphan*/ *,struct i40e_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i40e_client* registered_client ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,struct i40e_client*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void i40e_client_subtask(struct i40e_pf *pf)
{
	struct i40e_client *client = registered_client;
	struct i40e_client_instance *cdev;
	struct i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	int ret = 0;

	if (!test_and_clear_bit(__I40E_CLIENT_SERVICE_REQUESTED, pf->state))
		return;
	cdev = pf->cinst;

	/* If we're down or resetting, just bail */
	if (test_bit(__I40E_DOWN, pf->state) ||
	    test_bit(__I40E_CONFIG_BUSY, pf->state))
		return;

	if (!client || !cdev)
		return;

	/* Here we handle client opens. If the client is down, and
	 * the netdev is registered, then open the client.
	 */
	if (!test_bit(__I40E_CLIENT_INSTANCE_OPENED, &cdev->state)) {
		if (vsi->netdev_registered &&
		    client->ops && client->ops->open) {
			set_bit(__I40E_CLIENT_INSTANCE_OPENED, &cdev->state);
			ret = client->ops->open(&cdev->lan_info, client);
			if (ret) {
				/* Remove failed client instance */
				clear_bit(__I40E_CLIENT_INSTANCE_OPENED,
					  &cdev->state);
				i40e_client_del_instance(pf);
			}
		}
	}

	/* enable/disable PE TCP_ENA flag based on netdev down/up
	 */
	if (test_bit(__I40E_VSI_DOWN, vsi->state))
		i40e_client_update_vsi_ctxt(&cdev->lan_info, client,
					    0, 0, 0,
					    I40E_CLIENT_VSI_FLAG_TCP_ENABLE);
	else
		i40e_client_update_vsi_ctxt(&cdev->lan_info, client,
					    0, 0,
					    I40E_CLIENT_VSI_FLAG_TCP_ENABLE,
					    I40E_CLIENT_VSI_FLAG_TCP_ENABLE);
}