#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPA_VESWPORT_TRAP_IFACE_MCAST_MAC_CHANGE ; 
 int /*<<< orphan*/  OPA_VESWPORT_TRAP_IFACE_UCAST_MAC_CHANGE ; 
 int /*<<< orphan*/  opa_vnic_mac_send_event (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opa_vnic_set_rx_mode(struct net_device *netdev)
{
	opa_vnic_mac_send_event(netdev,
				OPA_VESWPORT_TRAP_IFACE_UCAST_MAC_CHANGE);

	opa_vnic_mac_send_event(netdev,
				OPA_VESWPORT_TRAP_IFACE_MCAST_MAC_CHANGE);
}