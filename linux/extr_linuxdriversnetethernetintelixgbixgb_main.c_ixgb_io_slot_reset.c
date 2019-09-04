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
struct pci_dev {int /*<<< orphan*/  devfn; } ;
struct net_device {int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct ixgb_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/  hw; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgb_get_ee_mac_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgb_reset (struct ixgb_adapter*) ; 
 int /*<<< orphan*/  ixgb_validate_eeprom_checksum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ixgb_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static pci_ers_result_t ixgb_io_slot_reset(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct ixgb_adapter *adapter = netdev_priv(netdev);

	if (pci_enable_device(pdev)) {
		netif_err(adapter, probe, adapter->netdev,
			  "Cannot re-enable PCI device after reset\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}

	/* Perform card reset only on one instance of the card */
	if (0 != PCI_FUNC (pdev->devfn))
		return PCI_ERS_RESULT_RECOVERED;

	pci_set_master(pdev);

	netif_carrier_off(netdev);
	netif_stop_queue(netdev);
	ixgb_reset(adapter);

	/* Make sure the EEPROM is good */
	if (!ixgb_validate_eeprom_checksum(&adapter->hw)) {
		netif_err(adapter, probe, adapter->netdev,
			  "After reset, the EEPROM checksum is not valid\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}
	ixgb_get_ee_mac_addr(&adapter->hw, netdev->dev_addr);
	memcpy(netdev->perm_addr, netdev->dev_addr, netdev->addr_len);

	if (!is_valid_ether_addr(netdev->perm_addr)) {
		netif_err(adapter, probe, adapter->netdev,
			  "After reset, invalid MAC address\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}

	return PCI_ERS_RESULT_RECOVERED;
}