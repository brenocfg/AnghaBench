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
struct octeon_device {TYPE_2__* pci_dev; TYPE_3__* props; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_4__ {int macaddr_is_admin_asgnd; int /*<<< orphan*/  hw_addr; } ;
struct lio {TYPE_1__ linfo; } ;
struct TYPE_6__ {struct net_device* netdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  NETDEV_CHANGEADDR ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void octeon_pf_changed_vf_macaddr(struct octeon_device *oct, u8 *mac)
{
	bool macaddr_changed = false;
	struct net_device *netdev;
	struct lio *lio;

	rtnl_lock();

	netdev = oct->props[0].netdev;
	lio = GET_LIO(netdev);

	lio->linfo.macaddr_is_admin_asgnd = true;

	if (!ether_addr_equal(netdev->dev_addr, mac)) {
		macaddr_changed = true;
		ether_addr_copy(netdev->dev_addr, mac);
		ether_addr_copy(((u8 *)&lio->linfo.hw_addr) + 2, mac);
		call_netdevice_notifiers(NETDEV_CHANGEADDR, netdev);
	}

	rtnl_unlock();

	if (macaddr_changed)
		dev_info(&oct->pci_dev->dev,
			 "PF changed VF's MAC address to %pM\n", mac);

	/* no need to notify the firmware of the macaddr change because
	 * the PF did that already
	 */
}