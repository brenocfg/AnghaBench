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
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  resource; int /*<<< orphan*/  dev; } ;
struct intel_th_drvdata {int dummy; } ;
struct intel_th {int /*<<< orphan*/  deactivate; int /*<<< orphan*/  activate; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAR_MASK ; 
 int /*<<< orphan*/  DEVICE_COUNT_RESOURCE ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 scalar_t__ IS_ERR (struct intel_th*) ; 
 int PTR_ERR (struct intel_th*) ; 
 struct intel_th* intel_th_alloc (int /*<<< orphan*/ *,struct intel_th_drvdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_th_pci_activate ; 
 int /*<<< orphan*/  intel_th_pci_deactivate ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions_request_all (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_th_pci_probe(struct pci_dev *pdev,
			      const struct pci_device_id *id)
{
	struct intel_th_drvdata *drvdata = (void *)id->driver_data;
	struct intel_th *th;
	int err;

	err = pcim_enable_device(pdev);
	if (err)
		return err;

	err = pcim_iomap_regions_request_all(pdev, BAR_MASK, DRIVER_NAME);
	if (err)
		return err;

	th = intel_th_alloc(&pdev->dev, drvdata, pdev->resource,
			    DEVICE_COUNT_RESOURCE, pdev->irq);
	if (IS_ERR(th))
		return PTR_ERR(th);

	th->activate   = intel_th_pci_activate;
	th->deactivate = intel_th_pci_deactivate;

	pci_set_master(pdev);

	return 0;
}