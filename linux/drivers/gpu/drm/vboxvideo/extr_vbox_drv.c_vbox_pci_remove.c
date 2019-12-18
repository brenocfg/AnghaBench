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
struct vbox_private {int /*<<< orphan*/  ddev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_unregister (int /*<<< orphan*/ *) ; 
 struct vbox_private* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  vbox_fbdev_fini (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_hw_fini (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_irq_fini (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_mm_fini (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_mode_fini (struct vbox_private*) ; 

__attribute__((used)) static void vbox_pci_remove(struct pci_dev *pdev)
{
	struct vbox_private *vbox = pci_get_drvdata(pdev);

	drm_dev_unregister(&vbox->ddev);
	vbox_fbdev_fini(vbox);
	vbox_irq_fini(vbox);
	vbox_mode_fini(vbox);
	vbox_mm_fini(vbox);
	vbox_hw_fini(vbox);
	drm_dev_put(&vbox->ddev);
}