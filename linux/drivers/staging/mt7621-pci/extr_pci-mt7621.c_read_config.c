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
typedef  int /*<<< orphan*/  u32 ;
struct mt7621_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RALINK_PCI_CONFIG_ADDR ; 
 int /*<<< orphan*/  RALINK_PCI_CONFIG_DATA ; 
 int /*<<< orphan*/  mt7621_pci_get_cfgaddr (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_read (struct mt7621_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_write (struct mt7621_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 read_config(struct mt7621_pcie *pcie, unsigned int dev, u32 reg)
{
	u32 address = mt7621_pci_get_cfgaddr(0, dev, 0, reg);

	pcie_write(pcie, address, RALINK_PCI_CONFIG_ADDR);
	return pcie_read(pcie, RALINK_PCI_CONFIG_DATA);
}