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
typedef  int /*<<< orphan*/  u32 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int subsystem_vendor; int subsystem_device; int /*<<< orphan*/  dev; scalar_t__ device; scalar_t__ vendor; } ;
struct octeon_device_priv {int dummy; } ;
struct octeon_device {int subsystem_id; struct pci_dev* pci_dev; int /*<<< orphan*/  msix_on; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LIO_FLAG_MSIX_ENABLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  liquidio_vf_remove (struct pci_dev*) ; 
 struct octeon_device* octeon_allocate_device (scalar_t__,int) ; 
 scalar_t__ octeon_device_init (struct octeon_device*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct octeon_device*) ; 

__attribute__((used)) static int
liquidio_vf_probe(struct pci_dev *pdev,
		  const struct pci_device_id *ent __attribute__((unused)))
{
	struct octeon_device *oct_dev = NULL;

	oct_dev = octeon_allocate_device(pdev->device,
					 sizeof(struct octeon_device_priv));

	if (!oct_dev) {
		dev_err(&pdev->dev, "Unable to allocate device\n");
		return -ENOMEM;
	}
	oct_dev->msix_on = LIO_FLAG_MSIX_ENABLED;

	dev_info(&pdev->dev, "Initializing device %x:%x.\n",
		 (u32)pdev->vendor, (u32)pdev->device);

	/* Assign octeon_device for this device to the private data area. */
	pci_set_drvdata(pdev, oct_dev);

	/* set linux specific device pointer */
	oct_dev->pci_dev = pdev;

	oct_dev->subsystem_id = pdev->subsystem_vendor |
		(pdev->subsystem_device << 16);

	if (octeon_device_init(oct_dev)) {
		liquidio_vf_remove(pdev);
		return -ENOMEM;
	}

	dev_dbg(&oct_dev->pci_dev->dev, "Device is ready\n");

	return 0;
}