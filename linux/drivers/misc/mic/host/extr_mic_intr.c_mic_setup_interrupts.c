#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct mic_device {TYPE_2__* intr_ops; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* enable_interrupts ) (struct mic_device*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int mic_setup_intx (struct mic_device*,struct pci_dev*) ; 
 int mic_setup_msi (struct mic_device*,struct pci_dev*) ; 
 int mic_setup_msix (struct mic_device*,struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct mic_device*) ; 

int mic_setup_interrupts(struct mic_device *mdev, struct pci_dev *pdev)
{
	int rc;

	rc = mic_setup_msix(mdev, pdev);
	if (!rc)
		goto done;

	rc = mic_setup_msi(mdev, pdev);
	if (!rc)
		goto done;

	rc = mic_setup_intx(mdev, pdev);
	if (rc) {
		dev_err(&mdev->pdev->dev, "no usable interrupts\n");
		return rc;
	}
done:
	mdev->intr_ops->enable_interrupts(mdev);
	return 0;
}