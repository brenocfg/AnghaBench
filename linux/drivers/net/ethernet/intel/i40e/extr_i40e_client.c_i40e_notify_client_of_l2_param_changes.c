#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_pf {TYPE_1__* pdev; struct i40e_client_instance* cinst; } ;
struct i40e_params {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  params; } ;
struct i40e_client_instance {TYPE_4__* client; TYPE_3__ lan_info; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_8__ {TYPE_2__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* l2_param_change ) (TYPE_3__*,TYPE_4__*,struct i40e_params*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __I40E_CLIENT_INSTANCE_OPENED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i40e_client_get_params (struct i40e_vsi*,struct i40e_params*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct i40e_params*,int) ; 
 int /*<<< orphan*/  memset (struct i40e_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_4__*,struct i40e_params*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void i40e_notify_client_of_l2_param_changes(struct i40e_vsi *vsi)
{
	struct i40e_pf *pf = vsi->back;
	struct i40e_client_instance *cdev = pf->cinst;
	struct i40e_params params;

	if (!cdev || !cdev->client)
		return;
	if (!cdev->client->ops || !cdev->client->ops->l2_param_change) {
		dev_dbg(&vsi->back->pdev->dev,
			"Cannot locate client instance l2_param_change routine\n");
		return;
	}
	if (!test_bit(__I40E_CLIENT_INSTANCE_OPENED, &cdev->state)) {
		dev_dbg(&vsi->back->pdev->dev, "Client is not open, abort l2 param change\n");
		return;
	}
	memset(&params, 0, sizeof(params));
	i40e_client_get_params(vsi, &params);
	memcpy(&cdev->lan_info.params, &params, sizeof(struct i40e_params));
	cdev->client->ops->l2_param_change(&cdev->lan_info, cdev->client,
					   &params);
}