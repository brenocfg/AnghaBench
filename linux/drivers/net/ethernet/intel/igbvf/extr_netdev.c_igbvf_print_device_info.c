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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igbvf_adapter {struct pci_dev* pdev; struct net_device* netdev; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ e1000_vfadapt_i350 ; 

__attribute__((used)) static void igbvf_print_device_info(struct igbvf_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;

	if (hw->mac.type == e1000_vfadapt_i350)
		dev_info(&pdev->dev, "Intel(R) I350 Virtual Function\n");
	else
		dev_info(&pdev->dev, "Intel(R) 82576 Virtual Function\n");
	dev_info(&pdev->dev, "Address: %pM\n", netdev->dev_addr);
}