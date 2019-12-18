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
struct TYPE_3__ {scalar_t__ fnum; } ;
struct qlcnic_adapter {int flags; TYPE_2__* ahw; TYPE_1__ fhash; } ;
struct TYPE_4__ {scalar_t__ vxlan_port; } ;

/* Variables and functions */
 int QLCNIC_ADD_VXLAN_PORT ; 
 int QLCNIC_DEL_VXLAN_PORT ; 
 int /*<<< orphan*/  qlcnic_prune_lb_filters (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_set_vxlan_parsing (struct qlcnic_adapter*,int) ; 
 scalar_t__ qlcnic_set_vxlan_port (struct qlcnic_adapter*) ; 

__attribute__((used)) static void qlcnic_83xx_periodic_tasks(struct qlcnic_adapter *adapter)
{
	if (adapter->fhash.fnum)
		qlcnic_prune_lb_filters(adapter);

	if (adapter->flags & QLCNIC_ADD_VXLAN_PORT) {
		if (qlcnic_set_vxlan_port(adapter))
			return;

		if (qlcnic_set_vxlan_parsing(adapter, true))
			return;

		adapter->flags &= ~QLCNIC_ADD_VXLAN_PORT;
	} else if (adapter->flags & QLCNIC_DEL_VXLAN_PORT) {
		if (qlcnic_set_vxlan_parsing(adapter, false))
			return;

		adapter->ahw->vxlan_port = 0;
		adapter->flags &= ~QLCNIC_DEL_VXLAN_PORT;
	}
}