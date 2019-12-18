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
typedef  scalar_t__ u64 ;
struct x86_cpu_id {scalar_t__ driver_data; } ;
struct pmc_reg_map {int /*<<< orphan*/  regmap_length; scalar_t__ slp_s0_offset; } ;
struct pmc_dev {int /*<<< orphan*/  pmc_xram_read_bit; int /*<<< orphan*/  lock; int /*<<< orphan*/  regbase; struct pmc_reg_map* map; scalar_t__ base_addr; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PHYS_PFN (scalar_t__) ; 
 scalar_t__ PMC_BASE_ADDR_DEFAULT ; 
 struct pmc_reg_map cnp_reg_map ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pmc_core_ids ; 
 int /*<<< orphan*/  ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lpit_read_residency_count_address (scalar_t__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ page_is_ram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pmc_dev*) ; 
 struct pmc_dev pmc ; 
 int /*<<< orphan*/  pmc_core_check_read_lock_bit () ; 
 int /*<<< orphan*/  pmc_core_dbgfs_register (struct pmc_dev*) ; 
 int /*<<< orphan*/  pmc_core_dmi_table ; 
 int /*<<< orphan*/  pmc_pci_ids ; 
 struct pmc_reg_map spt_reg_map ; 
 struct x86_cpu_id* x86_match_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmc_core_probe(struct platform_device *pdev)
{
	static bool device_initialized;
	struct pmc_dev *pmcdev = &pmc;
	const struct x86_cpu_id *cpu_id;
	u64 slp_s0_addr;

	if (device_initialized)
		return -ENODEV;

	cpu_id = x86_match_cpu(intel_pmc_core_ids);
	if (!cpu_id)
		return -ENODEV;

	pmcdev->map = (struct pmc_reg_map *)cpu_id->driver_data;

	/*
	 * Coffeelake has CPU ID of Kabylake and Cannonlake PCH. So here
	 * Sunrisepoint PCH regmap can't be used. Use Cannonlake PCH regmap
	 * in this case.
	 */
	if (pmcdev->map == &spt_reg_map && !pci_dev_present(pmc_pci_ids))
		pmcdev->map = &cnp_reg_map;

	if (lpit_read_residency_count_address(&slp_s0_addr)) {
		pmcdev->base_addr = PMC_BASE_ADDR_DEFAULT;

		if (page_is_ram(PHYS_PFN(pmcdev->base_addr)))
			return -ENODEV;
	} else {
		pmcdev->base_addr = slp_s0_addr - pmcdev->map->slp_s0_offset;
	}

	pmcdev->regbase = ioremap(pmcdev->base_addr,
				  pmcdev->map->regmap_length);
	if (!pmcdev->regbase)
		return -ENOMEM;

	mutex_init(&pmcdev->lock);
	platform_set_drvdata(pdev, pmcdev);
	pmcdev->pmc_xram_read_bit = pmc_core_check_read_lock_bit();
	dmi_check_system(pmc_core_dmi_table);

	pmc_core_dbgfs_register(pmcdev);

	device_initialized = true;
	dev_info(&pdev->dev, " initialized\n");

	return 0;
}