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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  QIB_DRV_NAME ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int pci_enable_pcie_error_reporting (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  qib_devinfo (struct pci_dev*,char*,int) ; 
 int /*<<< orphan*/  qib_early_err (int /*<<< orphan*/ *,char*,int) ; 

int qib_pcie_init(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int ret;

	ret = pci_enable_device(pdev);
	if (ret) {
		/*
		 * This can happen (in theory) iff:
		 * We did a chip reset, and then failed to reprogram the
		 * BAR, or the chip reset due to an internal error.  We then
		 * unloaded the driver and reloaded it.
		 *
		 * Both reset cases set the BAR back to initial state.  For
		 * the latter case, the AER sticky error bit at offset 0x718
		 * should be set, but the Linux kernel doesn't yet know
		 * about that, it appears.  If the original BAR was retained
		 * in the kernel data structures, this may be OK.
		 */
		qib_early_err(&pdev->dev, "pci enable failed: error %d\n",
			      -ret);
		goto done;
	}

	ret = pci_request_regions(pdev, QIB_DRV_NAME);
	if (ret) {
		qib_devinfo(pdev, "pci_request_regions fails: err %d\n", -ret);
		goto bail;
	}

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	if (ret) {
		/*
		 * If the 64 bit setup fails, try 32 bit.  Some systems
		 * do not setup 64 bit maps on systems with 2GB or less
		 * memory installed.
		 */
		ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (ret) {
			qib_devinfo(pdev, "Unable to set DMA mask: %d\n", ret);
			goto bail;
		}
		ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	} else
		ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	if (ret) {
		qib_early_err(&pdev->dev,
			      "Unable to set DMA consistent mask: %d\n", ret);
		goto bail;
	}

	pci_set_master(pdev);
	ret = pci_enable_pcie_error_reporting(pdev);
	if (ret) {
		qib_early_err(&pdev->dev,
			      "Unable to enable pcie error reporting: %d\n",
			      ret);
		ret = 0;
	}
	goto done;

bail:
	pci_disable_device(pdev);
	pci_release_regions(pdev);
done:
	return ret;
}