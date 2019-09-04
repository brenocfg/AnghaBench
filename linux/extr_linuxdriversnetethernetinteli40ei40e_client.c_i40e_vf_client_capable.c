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
typedef  int /*<<< orphan*/  u32 ;
struct i40e_pf {TYPE_1__* pdev; struct i40e_client_instance* cinst; } ;
struct i40e_client_instance {TYPE_3__* client; int /*<<< orphan*/  lan_info; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int (* vf_capable ) (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __I40E_CLIENT_INSTANCE_OPENED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int stub1 (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int i40e_vf_client_capable(struct i40e_pf *pf, u32 vf_id)
{
	struct i40e_client_instance *cdev = pf->cinst;
	int capable = false;

	if (!cdev || !cdev->client)
		goto out;
	if (!cdev->client->ops || !cdev->client->ops->vf_capable) {
		dev_dbg(&pf->pdev->dev,
			"Cannot locate client instance VF capability routine\n");
		goto out;
	}
	if (!test_bit(__I40E_CLIENT_INSTANCE_OPENED, &cdev->state))
		goto out;

	capable = cdev->client->ops->vf_capable(&cdev->lan_info,
						cdev->client,
						vf_id);
out:
	return capable;
}