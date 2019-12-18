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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct iavf_vsi {TYPE_3__* back; } ;
struct iavf_client_instance {TYPE_4__* client; int /*<<< orphan*/  lan_info; } ;
struct TYPE_8__ {TYPE_2__* ops; } ;
struct TYPE_7__ {TYPE_1__* pdev; struct iavf_client_instance* cinst; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* virtchnl_receive ) (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void iavf_notify_client_message(struct iavf_vsi *vsi, u8 *msg, u16 len)
{
	struct iavf_client_instance *cinst;

	if (!vsi)
		return;

	cinst = vsi->back->cinst;
	if (!cinst || !cinst->client || !cinst->client->ops ||
	    !cinst->client->ops->virtchnl_receive) {
		dev_dbg(&vsi->back->pdev->dev,
			"Cannot locate client instance virtchnl_receive function\n");
		return;
	}
	cinst->client->ops->virtchnl_receive(&cinst->lan_info,  cinst->client,
					     msg, len);
}