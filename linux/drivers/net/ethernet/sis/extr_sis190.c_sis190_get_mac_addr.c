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
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int sis190_get_mac_addr_from_apc (struct pci_dev*,struct net_device*) ; 
 int sis190_get_mac_addr_from_eeprom (struct pci_dev*,struct net_device*) ; 

__attribute__((used)) static int sis190_get_mac_addr(struct pci_dev *pdev, struct net_device *dev)
{
	int rc;

	rc = sis190_get_mac_addr_from_eeprom(pdev, dev);
	if (rc < 0) {
		u8 reg;

		pci_read_config_byte(pdev, 0x73, &reg);

		if (reg & 0x00000001)
			rc = sis190_get_mac_addr_from_apc(pdev, dev);
	}
	return rc;
}