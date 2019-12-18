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
struct iavf_vsi {TYPE_2__* back; } ;
struct iavf_params {int dummy; } ;
struct TYPE_9__ {struct iavf_params params; } ;
struct iavf_client_instance {TYPE_5__* client; TYPE_4__ lan_info; } ;
struct TYPE_10__ {TYPE_3__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* l2_param_change ) (TYPE_4__*,TYPE_5__*,struct iavf_params*) ;} ;
struct TYPE_7__ {TYPE_1__* pdev; struct iavf_client_instance* cinst; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iavf_client_get_params (struct iavf_vsi*,struct iavf_params*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_5__*,struct iavf_params*) ; 

void iavf_notify_client_l2_params(struct iavf_vsi *vsi)
{
	struct iavf_client_instance *cinst;
	struct iavf_params params;

	if (!vsi)
		return;

	cinst = vsi->back->cinst;

	if (!cinst || !cinst->client || !cinst->client->ops ||
	    !cinst->client->ops->l2_param_change) {
		dev_dbg(&vsi->back->pdev->dev,
			"Cannot locate client instance l2_param_change function\n");
		return;
	}
	iavf_client_get_params(vsi, &params);
	cinst->lan_info.params = params;
	cinst->client->ops->l2_param_change(&cinst->lan_info, cinst->client,
					    &params);
}