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
struct qxl_device {int dummy; } ;
struct pci_dev {int dummy; } ;
struct drm_device {struct qxl_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_RSRC_LEGACY_IO ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 scalar_t__ is_vga (struct pci_dev*) ; 
 int /*<<< orphan*/  kfree (struct qxl_device*) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  qxl_device_fini (struct qxl_device*) ; 
 int /*<<< orphan*/  qxl_modeset_fini (struct qxl_device*) ; 
 int /*<<< orphan*/  vga_put (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qxl_pci_remove(struct pci_dev *pdev)
{
	struct drm_device *dev = pci_get_drvdata(pdev);
	struct qxl_device *qdev = dev->dev_private;

	drm_dev_unregister(dev);

	qxl_modeset_fini(qdev);
	qxl_device_fini(qdev);
	if (is_vga(pdev))
		vga_put(pdev, VGA_RSRC_LEGACY_IO);

	dev->dev_private = NULL;
	kfree(qdev);
	drm_dev_put(dev);
}