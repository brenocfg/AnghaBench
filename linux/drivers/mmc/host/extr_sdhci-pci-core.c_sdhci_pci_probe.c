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
struct sdhci_pci_slot {int dummy; } ;
struct sdhci_pci_fixes {int (* probe ) (struct sdhci_pci_chip*) ;scalar_t__ allow_runtime_pm; int /*<<< orphan*/  quirks2; int /*<<< orphan*/  quirks; } ;
struct sdhci_pci_chip {int num_slots; int pm_retune; int rpm_retune; scalar_t__ allow_runtime_pm; struct sdhci_pci_slot** slots; struct sdhci_pci_fixes const* fixes; int /*<<< orphan*/  quirks2; int /*<<< orphan*/  quirks; struct pci_dev* pdev; } ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; scalar_t__ revision; scalar_t__ device; scalar_t__ vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sdhci_pci_slot*) ; 
 int MAX_SLOTS ; 
 int /*<<< orphan*/  PCI_SLOT_INFO ; 
 int PCI_SLOT_INFO_FIRST_BAR_MASK ; 
 int PCI_SLOT_INFO_SLOTS (int) ; 
 int PTR_ERR (struct sdhci_pci_slot*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,int) ; 
 struct sdhci_pci_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct sdhci_pci_chip*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 struct sdhci_pci_slot* sdhci_pci_probe_slot (struct pci_dev*,struct sdhci_pci_chip*,int,int) ; 
 int /*<<< orphan*/  sdhci_pci_remove_slot (struct sdhci_pci_slot*) ; 
 int /*<<< orphan*/  sdhci_pci_runtime_pm_allow (int /*<<< orphan*/ *) ; 
 int stub1 (struct sdhci_pci_chip*) ; 

__attribute__((used)) static int sdhci_pci_probe(struct pci_dev *pdev,
				     const struct pci_device_id *ent)
{
	struct sdhci_pci_chip *chip;
	struct sdhci_pci_slot *slot;

	u8 slots, first_bar;
	int ret, i;

	BUG_ON(pdev == NULL);
	BUG_ON(ent == NULL);

	dev_info(&pdev->dev, "SDHCI controller found [%04x:%04x] (rev %x)\n",
		 (int)pdev->vendor, (int)pdev->device, (int)pdev->revision);

	ret = pci_read_config_byte(pdev, PCI_SLOT_INFO, &slots);
	if (ret)
		return ret;

	slots = PCI_SLOT_INFO_SLOTS(slots) + 1;
	dev_dbg(&pdev->dev, "found %d slot(s)\n", slots);

	BUG_ON(slots > MAX_SLOTS);

	ret = pci_read_config_byte(pdev, PCI_SLOT_INFO, &first_bar);
	if (ret)
		return ret;

	first_bar &= PCI_SLOT_INFO_FIRST_BAR_MASK;

	if (first_bar > 5) {
		dev_err(&pdev->dev, "Invalid first BAR. Aborting.\n");
		return -ENODEV;
	}

	ret = pcim_enable_device(pdev);
	if (ret)
		return ret;

	chip = devm_kzalloc(&pdev->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->pdev = pdev;
	chip->fixes = (const struct sdhci_pci_fixes *)ent->driver_data;
	if (chip->fixes) {
		chip->quirks = chip->fixes->quirks;
		chip->quirks2 = chip->fixes->quirks2;
		chip->allow_runtime_pm = chip->fixes->allow_runtime_pm;
	}
	chip->num_slots = slots;
	chip->pm_retune = true;
	chip->rpm_retune = true;

	pci_set_drvdata(pdev, chip);

	if (chip->fixes && chip->fixes->probe) {
		ret = chip->fixes->probe(chip);
		if (ret)
			return ret;
	}

	slots = chip->num_slots;	/* Quirk may have changed this */

	for (i = 0; i < slots; i++) {
		slot = sdhci_pci_probe_slot(pdev, chip, first_bar, i);
		if (IS_ERR(slot)) {
			for (i--; i >= 0; i--)
				sdhci_pci_remove_slot(chip->slots[i]);
			return PTR_ERR(slot);
		}

		chip->slots[i] = slot;
	}

	if (chip->allow_runtime_pm)
		sdhci_pci_runtime_pm_allow(&pdev->dev);

	return 0;
}