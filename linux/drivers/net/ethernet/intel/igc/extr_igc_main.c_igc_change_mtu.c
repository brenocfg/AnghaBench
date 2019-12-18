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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int mtu; } ;
struct igc_adapter {int max_frame_size; int /*<<< orphan*/  state; struct pci_dev* pdev; } ;

/* Variables and functions */
 int ETH_FCS_LEN ; 
 int ETH_FRAME_LEN ; 
 int ETH_HLEN ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  __IGC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  igc_down (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_reset (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_up (struct igc_adapter*) ; 
 struct igc_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int igc_change_mtu(struct net_device *netdev, int new_mtu)
{
	int max_frame = new_mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	struct igc_adapter *adapter = netdev_priv(netdev);
	struct pci_dev *pdev = adapter->pdev;

	/* adjust max frame to be at least the size of a standard frame */
	if (max_frame < (ETH_FRAME_LEN + ETH_FCS_LEN))
		max_frame = ETH_FRAME_LEN + ETH_FCS_LEN;

	while (test_and_set_bit(__IGC_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	/* igc_down has a dependency on max_frame_size */
	adapter->max_frame_size = max_frame;

	if (netif_running(netdev))
		igc_down(adapter);

	dev_info(&pdev->dev, "changing MTU from %d to %d\n",
		 netdev->mtu, new_mtu);
	netdev->mtu = new_mtu;

	if (netif_running(netdev))
		igc_up(adapter);
	else
		igc_reset(adapter);

	clear_bit(__IGC_RESETTING, &adapter->state);

	return 0;
}