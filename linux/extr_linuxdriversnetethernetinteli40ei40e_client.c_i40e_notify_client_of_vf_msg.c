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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_pf {TYPE_1__* pdev; struct i40e_client_instance* cinst; } ;
struct i40e_client_instance {TYPE_3__* client; int /*<<< orphan*/  lan_info; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* virtchnl_receive ) (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __I40E_CLIENT_INSTANCE_OPENED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
i40e_notify_client_of_vf_msg(struct i40e_vsi *vsi, u32 vf_id, u8 *msg, u16 len)
{
	struct i40e_pf *pf = vsi->back;
	struct i40e_client_instance *cdev = pf->cinst;

	if (!cdev || !cdev->client)
		return;
	if (!cdev->client->ops || !cdev->client->ops->virtchnl_receive) {
		dev_dbg(&pf->pdev->dev,
			"Cannot locate client instance virtual channel receive routine\n");
		return;
	}
	if (!test_bit(__I40E_CLIENT_INSTANCE_OPENED, &cdev->state)) {
		dev_dbg(&pf->pdev->dev, "Client is not open, abort virtchnl_receive\n");
		return;
	}
	cdev->client->ops->virtchnl_receive(&cdev->lan_info, cdev->client,
					    vf_id, msg, len);
}