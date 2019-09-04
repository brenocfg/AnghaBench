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
struct i40evf_adapter {TYPE_1__* pdev; struct i40e_client_instance* cinst; } ;
struct i40e_vsi {struct i40evf_adapter* back; } ;
struct i40e_client_instance {int /*<<< orphan*/  state; int /*<<< orphan*/  lan_info; TYPE_3__* client; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* close ) (int /*<<< orphan*/ *,TYPE_3__*,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __I40E_CLIENT_INSTANCE_OPENED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i40evf_client_release_qvlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_3__*,int) ; 

void i40evf_notify_client_close(struct i40e_vsi *vsi, bool reset)
{
	struct i40evf_adapter *adapter = vsi->back;
	struct i40e_client_instance *cinst = adapter->cinst;

	if (!cinst || !cinst->client || !cinst->client->ops ||
	    !cinst->client->ops->close) {
		dev_dbg(&vsi->back->pdev->dev,
			"Cannot locate client instance close function\n");
		return;
	}
	cinst->client->ops->close(&cinst->lan_info, cinst->client, reset);
	i40evf_client_release_qvlist(&cinst->lan_info);
	clear_bit(__I40E_CLIENT_INSTANCE_OPENED, &cinst->state);
}