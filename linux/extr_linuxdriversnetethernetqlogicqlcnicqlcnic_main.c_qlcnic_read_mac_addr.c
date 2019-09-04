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
typedef  int /*<<< orphan*/  u8 ;
struct qlcnic_adapter {int /*<<< orphan*/ * mac_addr; TYPE_1__* ahw; struct pci_dev* pdev; struct net_device* netdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int addr_len; int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci_func; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int qlcnic_get_mac_address (struct qlcnic_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int qlcnic_read_mac_addr(struct qlcnic_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	u8 mac_addr[ETH_ALEN];
	int ret;

	ret = qlcnic_get_mac_address(adapter, mac_addr,
				     adapter->ahw->pci_func);
	if (ret)
		return ret;

	memcpy(netdev->dev_addr, mac_addr, ETH_ALEN);
	memcpy(adapter->mac_addr, netdev->dev_addr, netdev->addr_len);

	/* set station address */

	if (!is_valid_ether_addr(netdev->dev_addr))
		dev_warn(&pdev->dev, "Bad MAC address %pM.\n",
					netdev->dev_addr);

	return 0;
}