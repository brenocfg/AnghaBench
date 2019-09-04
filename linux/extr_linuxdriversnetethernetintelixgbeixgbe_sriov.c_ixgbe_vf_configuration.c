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
struct pci_dev {int dummy; } ;
struct ixgbe_adapter {TYPE_1__* vfinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  vf_mac_addresses; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 struct ixgbe_adapter* pci_get_drvdata (struct pci_dev*) ; 

int ixgbe_vf_configuration(struct pci_dev *pdev, unsigned int event_mask)
{
	struct ixgbe_adapter *adapter = pci_get_drvdata(pdev);
	unsigned int vfn = (event_mask & 0x3f);

	bool enable = ((event_mask & 0x10000000U) != 0);

	if (enable)
		eth_zero_addr(adapter->vfinfo[vfn].vf_mac_addresses);

	return 0;
}