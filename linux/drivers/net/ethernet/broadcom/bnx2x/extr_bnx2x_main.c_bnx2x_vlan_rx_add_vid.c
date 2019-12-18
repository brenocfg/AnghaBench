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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct bnx2x_vlan_entry {int hw; int /*<<< orphan*/  link; int /*<<< orphan*/  vid; } ;
struct bnx2x {int /*<<< orphan*/  vlan_reg; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int /*<<< orphan*/  bnx2x_vlan_configure (struct bnx2x*,int) ; 
 struct bnx2x_vlan_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int bnx2x_vlan_rx_add_vid(struct net_device *dev, __be16 proto, u16 vid)
{
	struct bnx2x *bp = netdev_priv(dev);
	struct bnx2x_vlan_entry *vlan;

	DP(NETIF_MSG_IFUP, "Adding VLAN %d\n", vid);

	vlan = kmalloc(sizeof(*vlan), GFP_KERNEL);
	if (!vlan)
		return -ENOMEM;

	vlan->vid = vid;
	vlan->hw = false;
	list_add_tail(&vlan->link, &bp->vlan_reg);

	if (netif_running(dev))
		bnx2x_vlan_configure(bp, true);

	return 0;
}