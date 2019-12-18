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
struct net_device {scalar_t__ hw_enc_features; } ;
struct be_adapter {int flags; scalar_t__ vxlan_port; int /*<<< orphan*/  if_handle; struct net_device* netdev; } ;

/* Variables and functions */
 int BE_FLAGS_VXLAN_OFFLOADS ; 
 int /*<<< orphan*/  OP_CONVERT_TUNNEL_TO_NORMAL ; 
 int /*<<< orphan*/  be_cmd_manage_iface (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_cmd_set_vxlan_port (struct be_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_disable_vxlan_offloads(struct be_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	if (adapter->flags & BE_FLAGS_VXLAN_OFFLOADS)
		be_cmd_manage_iface(adapter, adapter->if_handle,
				    OP_CONVERT_TUNNEL_TO_NORMAL);

	if (adapter->vxlan_port)
		be_cmd_set_vxlan_port(adapter, 0);

	adapter->flags &= ~BE_FLAGS_VXLAN_OFFLOADS;
	adapter->vxlan_port = 0;

	netdev->hw_enc_features = 0;
}