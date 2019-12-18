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
struct pmc_reg_map {int dummy; } ;
struct pmc_dev {int init; int /*<<< orphan*/  regmap; struct pmc_reg_map const* map; int /*<<< orphan*/  base_addr; } ;
struct pmc_data {struct pmc_reg_map* map; } ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BASE_ADDR_MASK ; 
 int /*<<< orphan*/  ACPI_BASE_ADDR_OFFSET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PMC_BASE_ADDR_MASK ; 
 int /*<<< orphan*/  PMC_BASE_ADDR_OFFSET ; 
 int /*<<< orphan*/  PMC_MMIO_REG_LEN ; 
 int /*<<< orphan*/  acpi_base_addr ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pm_power_off ; 
 int /*<<< orphan*/  pmc_dbgfs_register (struct pmc_dev*) ; 
 struct pmc_dev pmc_device ; 
 int /*<<< orphan*/  pmc_hw_reg_setup (struct pmc_dev*) ; 
 int /*<<< orphan*/ * pmc_power_off ; 
 int pmc_setup_clks (struct pci_dev*,int /*<<< orphan*/ ,struct pmc_data const*) ; 

__attribute__((used)) static int pmc_setup_dev(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct pmc_dev *pmc = &pmc_device;
	const struct pmc_data *data = (struct pmc_data *)ent->driver_data;
	const struct pmc_reg_map *map = data->map;
	int ret;

	/* Obtain ACPI base address */
	pci_read_config_dword(pdev, ACPI_BASE_ADDR_OFFSET, &acpi_base_addr);
	acpi_base_addr &= ACPI_BASE_ADDR_MASK;

	/* Install power off function */
	if (acpi_base_addr != 0 && pm_power_off == NULL)
		pm_power_off = pmc_power_off;

	pci_read_config_dword(pdev, PMC_BASE_ADDR_OFFSET, &pmc->base_addr);
	pmc->base_addr &= PMC_BASE_ADDR_MASK;

	pmc->regmap = ioremap_nocache(pmc->base_addr, PMC_MMIO_REG_LEN);
	if (!pmc->regmap) {
		dev_err(&pdev->dev, "error: ioremap failed\n");
		return -ENOMEM;
	}

	pmc->map = map;

	/* PMC hardware registers setup */
	pmc_hw_reg_setup(pmc);

	pmc_dbgfs_register(pmc);

	/* Register platform clocks - PMC_PLT_CLK [0..5] */
	ret = pmc_setup_clks(pdev, pmc->regmap, data);
	if (ret)
		dev_warn(&pdev->dev, "platform clocks register failed: %d\n",
			 ret);

	pmc->init = true;
	return ret;
}