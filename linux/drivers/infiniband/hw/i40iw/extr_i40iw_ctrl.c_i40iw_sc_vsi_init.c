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
struct i40iw_vsi_init_info {TYPE_1__* params; int /*<<< orphan*/  exception_lan_queue; int /*<<< orphan*/  back_vsi; int /*<<< orphan*/  dev; } ;
struct i40iw_sc_vsi {TYPE_2__* qos; int /*<<< orphan*/  dev; int /*<<< orphan*/  exception_lan_queue; int /*<<< orphan*/  mtu; int /*<<< orphan*/  back_vsi; } ;
struct TYPE_4__ {int /*<<< orphan*/  qplist; int /*<<< orphan*/  lock; int /*<<< orphan*/  qs_handle; } ;
struct TYPE_3__ {int /*<<< orphan*/ * qs_handle_list; int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_DEBUG_DCB ; 
 int I40IW_MAX_USER_PRIORITY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_fill_qos_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void i40iw_sc_vsi_init(struct i40iw_sc_vsi *vsi, struct i40iw_vsi_init_info *info)
{
	int i;

	vsi->dev = info->dev;
	vsi->back_vsi = info->back_vsi;
	vsi->mtu = info->params->mtu;
	vsi->exception_lan_queue = info->exception_lan_queue;
	i40iw_fill_qos_list(info->params->qs_handle_list);

	for (i = 0; i < I40IW_MAX_USER_PRIORITY; i++) {
		vsi->qos[i].qs_handle = info->params->qs_handle_list[i];
		i40iw_debug(vsi->dev, I40IW_DEBUG_DCB, "qset[%d]: %d\n", i,
			    vsi->qos[i].qs_handle);
		spin_lock_init(&vsi->qos[i].lock);
		INIT_LIST_HEAD(&vsi->qos[i].qplist);
	}
}