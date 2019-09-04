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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ioatdma_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_resume (struct ioatdma_device*) ; 
 struct ioatdma_device* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void ioat_pcie_error_resume(struct pci_dev *pdev)
{
	struct ioatdma_device *ioat_dma = pci_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "%s: AER handling resuming\n", DRV_NAME);

	/* initialize and bring everything back */
	ioat_resume(ioat_dma);
}