#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unique ;
struct TYPE_6__ {TYPE_2__* parent; } ;
struct virtio_device {TYPE_3__ dev; struct drm_device* priv; } ;
struct pci_dev {int class; int /*<<< orphan*/  dev; } ;
struct drm_driver {int dummy; } ;
struct drm_device {struct pci_dev* pdev; } ;
struct TYPE_5__ {TYPE_1__* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,char*,char const*) ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PCI_CLASS_DISPLAY_VGA ; 
 int PTR_ERR (struct drm_device*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 struct drm_device* drm_dev_alloc (struct drm_driver*,TYPE_3__*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int drm_dev_set_unique (struct drm_device*,char*) ; 
 int /*<<< orphan*/  drm_dev_unref (struct drm_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct pci_dev* to_pci_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  virtio_pci_kick_out_firmware_fb (struct pci_dev*) ; 

int drm_virtio_init(struct drm_driver *driver, struct virtio_device *vdev)
{
	struct drm_device *dev;
	int ret;

	dev = drm_dev_alloc(driver, &vdev->dev);
	if (IS_ERR(dev))
		return PTR_ERR(dev);
	vdev->priv = dev;

	if (strcmp(vdev->dev.parent->bus->name, "pci") == 0) {
		struct pci_dev *pdev = to_pci_dev(vdev->dev.parent);
		const char *pname = dev_name(&pdev->dev);
		bool vga = (pdev->class >> 8) == PCI_CLASS_DISPLAY_VGA;
		char unique[20];

		DRM_INFO("pci: %s detected at %s\n",
			 vga ? "virtio-vga" : "virtio-gpu-pci",
			 pname);
		dev->pdev = pdev;
		if (vga)
			virtio_pci_kick_out_firmware_fb(pdev);

		snprintf(unique, sizeof(unique), "pci:%s", pname);
		ret = drm_dev_set_unique(dev, unique);
		if (ret)
			goto err_free;

	}

	ret = drm_dev_register(dev, 0);
	if (ret)
		goto err_free;

	return 0;

err_free:
	drm_dev_unref(dev);
	return ret;
}