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
struct opa_vnic_adapter {int /*<<< orphan*/  netdev; TYPE_1__* rn_ops; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int (* ndo_open ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  OPA_VESWPORT_TRAP_ETH_LINK_STATUS_CHANGE ; 
 struct opa_vnic_adapter* opa_vnic_priv (struct net_device*) ; 
 int /*<<< orphan*/  opa_vnic_update_state (struct opa_vnic_adapter*,int) ; 
 int /*<<< orphan*/  opa_vnic_vema_report_event (struct opa_vnic_adapter*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_dbg (char*,int) ; 

__attribute__((used)) static int opa_netdev_open(struct net_device *netdev)
{
	struct opa_vnic_adapter *adapter = opa_vnic_priv(netdev);
	int rc;

	rc = adapter->rn_ops->ndo_open(adapter->netdev);
	if (rc) {
		v_dbg("open failed %d\n", rc);
		return rc;
	}

	/* Update status and send trap */
	opa_vnic_update_state(adapter, true);
	opa_vnic_vema_report_event(adapter,
				   OPA_VESWPORT_TRAP_ETH_LINK_STATUS_CHANGE);
	return 0;
}