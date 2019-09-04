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
typedef  int /*<<< orphan*/  u8 ;
struct pch_phub_reg {int /*<<< orphan*/  pch_phub_extrom_base_address; int /*<<< orphan*/  pdev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct pch_phub_reg* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pch_phub_read_gbe_mac_addr (struct pch_phub_reg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_map_rom (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_rom (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t show_pch_mac(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	u8 mac[8];
	struct pch_phub_reg *chip = dev_get_drvdata(dev);
	ssize_t rom_size;

	chip->pch_phub_extrom_base_address = pci_map_rom(chip->pdev, &rom_size);
	if (!chip->pch_phub_extrom_base_address)
		return -ENOMEM;

	pch_phub_read_gbe_mac_addr(chip, mac);
	pci_unmap_rom(chip->pdev, chip->pch_phub_extrom_base_address);

	return sprintf(buf, "%pM\n", mac);
}