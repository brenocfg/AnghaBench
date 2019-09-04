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
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 struct pch_phub_reg* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mac_pton (char const*,int /*<<< orphan*/ *) ; 
 int pch_phub_write_gbe_mac_addr (struct pch_phub_reg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_map_rom (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_unmap_rom (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t store_pch_mac(struct device *dev, struct device_attribute *attr,
			     const char *buf, size_t count)
{
	u8 mac[ETH_ALEN];
	ssize_t rom_size;
	struct pch_phub_reg *chip = dev_get_drvdata(dev);
	int ret;

	if (!mac_pton(buf, mac))
		return -EINVAL;

	chip->pch_phub_extrom_base_address = pci_map_rom(chip->pdev, &rom_size);
	if (!chip->pch_phub_extrom_base_address)
		return -ENOMEM;

	ret = pch_phub_write_gbe_mac_addr(chip, mac);
	pci_unmap_rom(chip->pdev, chip->pch_phub_extrom_base_address);
	if (ret)
		return ret;

	return count;
}