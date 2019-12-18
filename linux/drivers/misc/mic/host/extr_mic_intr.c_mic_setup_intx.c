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
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct mic_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mic_interrupt ; 
 int /*<<< orphan*/  mic_release_callbacks (struct mic_device*) ; 
 int mic_setup_callbacks (struct mic_device*) ; 
 int /*<<< orphan*/  mic_thread_fn ; 
 int /*<<< orphan*/  pci_intx (struct pci_dev*,int) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mic_device*) ; 

__attribute__((used)) static int mic_setup_intx(struct mic_device *mdev, struct pci_dev *pdev)
{
	int rc;

	/* Enable intx */
	pci_intx(pdev, 1);
	rc = mic_setup_callbacks(mdev);
	if (rc) {
		dev_err(&pdev->dev, "Error setting up callbacks\n");
		goto err_nomem;
	}

	rc = request_threaded_irq(pdev->irq, mic_interrupt, mic_thread_fn,
				  IRQF_SHARED, "mic-intx", mdev);
	if (rc)
		goto err;

	dev_dbg(&pdev->dev, "intx irq setup\n");
	return 0;
err:
	mic_release_callbacks(mdev);
err_nomem:
	return rc;
}