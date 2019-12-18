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
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; scalar_t__ d3cold_delay; int /*<<< orphan*/  irq; int /*<<< orphan*/ * resource; } ;
struct intel_lpss_platform_info {int /*<<< orphan*/  irq; int /*<<< orphan*/ * mem; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct intel_lpss_platform_info* devm_kmemdup (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 int intel_lpss_probe (int /*<<< orphan*/ *,struct intel_lpss_platform_info*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_try_set_mwi (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_lpss_pci_probe(struct pci_dev *pdev,
				const struct pci_device_id *id)
{
	struct intel_lpss_platform_info *info;
	int ret;

	ret = pcim_enable_device(pdev);
	if (ret)
		return ret;

	info = devm_kmemdup(&pdev->dev, (void *)id->driver_data, sizeof(*info),
			    GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->mem = &pdev->resource[0];
	info->irq = pdev->irq;

	pdev->d3cold_delay = 0;

	/* Probably it is enough to set this for iDMA capable devices only */
	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	ret = intel_lpss_probe(&pdev->dev, info);
	if (ret)
		return ret;

	pm_runtime_put(&pdev->dev);
	pm_runtime_allow(&pdev->dev);

	return 0;
}