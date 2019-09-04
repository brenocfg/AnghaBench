#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ parent; } ;
struct solo_dev {int /*<<< orphan*/  v4l2_dev; scalar_t__ reg_base; TYPE_1__ dev; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct solo_dev*) ; 
 int /*<<< orphan*/  kfree (struct solo_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  solo_disp_exit (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_enc_exit (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_enc_v4l2_exit (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_g723_exit (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_gpio_exit (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_i2c_exit (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_irq_off (struct solo_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_p2m_exit (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_v4l2_exit (struct solo_dev*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_solo_dev(struct solo_dev *solo_dev)
{
	struct pci_dev *pdev = solo_dev->pdev;

	if (solo_dev->dev.parent)
		device_unregister(&solo_dev->dev);

	if (solo_dev->reg_base) {
		/* Bring down the sub-devices first */
		solo_g723_exit(solo_dev);
		solo_enc_v4l2_exit(solo_dev);
		solo_enc_exit(solo_dev);
		solo_v4l2_exit(solo_dev);
		solo_disp_exit(solo_dev);
		solo_gpio_exit(solo_dev);
		solo_p2m_exit(solo_dev);
		solo_i2c_exit(solo_dev);

		/* Now cleanup the PCI device */
		solo_irq_off(solo_dev, ~0);
		free_irq(pdev->irq, solo_dev);
		pci_iounmap(pdev, solo_dev->reg_base);
	}

	pci_release_regions(pdev);
	pci_disable_device(pdev);
	v4l2_device_unregister(&solo_dev->v4l2_dev);
	pci_set_drvdata(pdev, NULL);

	kfree(solo_dev);
}