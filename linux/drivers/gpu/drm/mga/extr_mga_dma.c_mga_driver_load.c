#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_4__* pdev; void* dev_private; TYPE_8__* agp; } ;
struct TYPE_11__ {unsigned long chipset; int /*<<< orphan*/  mmio_size; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  usec_timeout; } ;
typedef  TYPE_3__ drm_mga_private_t ;
struct TYPE_13__ {int /*<<< orphan*/  agp_mtrr; } ;
struct TYPE_12__ {int device; TYPE_2__* bus; } ;
struct TYPE_10__ {TYPE_1__* self; } ;
struct TYPE_9__ {int vendor; int device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MGA_DEFAULT_USEC_TIMEOUT ; 
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int drm_vblank_init (struct drm_device*,int) ; 
 int /*<<< orphan*/  kfree (TYPE_8__*) ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mga_driver_unload (struct drm_device*) ; 
 int /*<<< orphan*/  pci_resource_len (TYPE_4__*,int) ; 
 int /*<<< orphan*/  pci_resource_start (TYPE_4__*,int) ; 
 int /*<<< orphan*/  pci_set_master (TYPE_4__*) ; 

int mga_driver_load(struct drm_device *dev, unsigned long flags)
{
	drm_mga_private_t *dev_priv;
	int ret;

	/* There are PCI versions of the G450.  These cards have the
	 * same PCI ID as the AGP G450, but have an additional PCI-to-PCI
	 * bridge chip.  We detect these cards, which are not currently
	 * supported by this driver, by looking at the device ID of the
	 * bus the "card" is on.  If vendor is 0x3388 (Hint Corp) and the
	 * device is 0x0021 (HB6 Universal PCI-PCI bridge), we reject the
	 * device.
	 */
	if ((dev->pdev->device == 0x0525) && dev->pdev->bus->self
	    && (dev->pdev->bus->self->vendor == 0x3388)
	    && (dev->pdev->bus->self->device == 0x0021)
	    && dev->agp) {
		/* FIXME: This should be quirked in the pci core, but oh well
		 * the hw probably stopped existing. */
		arch_phys_wc_del(dev->agp->agp_mtrr);
		kfree(dev->agp);
		dev->agp = NULL;
	}
	dev_priv = kzalloc(sizeof(drm_mga_private_t), GFP_KERNEL);
	if (!dev_priv)
		return -ENOMEM;

	dev->dev_private = (void *)dev_priv;

	dev_priv->usec_timeout = MGA_DEFAULT_USEC_TIMEOUT;
	dev_priv->chipset = flags;

	pci_set_master(dev->pdev);

	dev_priv->mmio_base = pci_resource_start(dev->pdev, 1);
	dev_priv->mmio_size = pci_resource_len(dev->pdev, 1);

	ret = drm_vblank_init(dev, 1);

	if (ret) {
		(void) mga_driver_unload(dev);
		return ret;
	}

	return 0;
}