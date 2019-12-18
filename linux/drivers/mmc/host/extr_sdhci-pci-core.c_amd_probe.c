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
struct sdhci_pci_chip {int /*<<< orphan*/  quirks2; } ;
struct pci_dev {int revision; } ;
typedef  enum amd_chipset_gen { ____Placeholder_amd_chipset_gen } amd_chipset_gen ;

/* Variables and functions */
 int AMD_CHIPSET_BEFORE_ML ; 
 int AMD_CHIPSET_CZ ; 
 int AMD_CHIPSET_NL ; 
 int AMD_CHIPSET_UNKNOWN ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_AMD_HUDSON2_SMBUS ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_AMD_KERNCZ_SMBUS ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_AMD ; 
 int /*<<< orphan*/  SDHCI_QUIRK2_CLEAR_TRANSFERMODE_REG_BEFORE_CMD ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amd_probe(struct sdhci_pci_chip *chip)
{
	struct pci_dev	*smbus_dev;
	enum amd_chipset_gen gen;

	smbus_dev = pci_get_device(PCI_VENDOR_ID_AMD,
			PCI_DEVICE_ID_AMD_HUDSON2_SMBUS, NULL);
	if (smbus_dev) {
		gen = AMD_CHIPSET_BEFORE_ML;
	} else {
		smbus_dev = pci_get_device(PCI_VENDOR_ID_AMD,
				PCI_DEVICE_ID_AMD_KERNCZ_SMBUS, NULL);
		if (smbus_dev) {
			if (smbus_dev->revision < 0x51)
				gen = AMD_CHIPSET_CZ;
			else
				gen = AMD_CHIPSET_NL;
		} else {
			gen = AMD_CHIPSET_UNKNOWN;
		}
	}

	if (gen == AMD_CHIPSET_BEFORE_ML || gen == AMD_CHIPSET_CZ)
		chip->quirks2 |= SDHCI_QUIRK2_CLEAR_TRANSFERMODE_REG_BEFORE_CMD;

	return 0;
}