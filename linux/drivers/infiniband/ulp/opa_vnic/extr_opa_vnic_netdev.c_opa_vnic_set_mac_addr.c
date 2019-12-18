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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  uc_macs_gen_count; } ;
struct TYPE_4__ {TYPE_1__ vport; } ;
struct opa_vnic_adapter {TYPE_2__ info; int /*<<< orphan*/  lock; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  OPA_VESWPORT_TRAP_IFACE_UCAST_MAC_CHANGE ; 
 int eth_mac_addr (struct net_device*,void*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct opa_vnic_adapter* opa_vnic_priv (struct net_device*) ; 
 int /*<<< orphan*/  opa_vnic_vema_report_event (struct opa_vnic_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opa_vnic_set_mac_addr(struct net_device *netdev, void *addr)
{
	struct opa_vnic_adapter *adapter = opa_vnic_priv(netdev);
	struct sockaddr *sa = addr;
	int rc;

	if (!memcmp(netdev->dev_addr, sa->sa_data, ETH_ALEN))
		return 0;

	mutex_lock(&adapter->lock);
	rc = eth_mac_addr(netdev, addr);
	mutex_unlock(&adapter->lock);
	if (rc)
		return rc;

	adapter->info.vport.uc_macs_gen_count++;
	opa_vnic_vema_report_event(adapter,
				   OPA_VESWPORT_TRAP_IFACE_UCAST_MAC_CHANGE);
	return 0;
}