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
struct drm_device {int /*<<< orphan*/  pdev; TYPE_2__* agp; } ;
struct TYPE_3__ {int aper_size; int /*<<< orphan*/  aper_base; } ;
struct TYPE_4__ {TYPE_1__ agp_info; int /*<<< orphan*/  agp_mtrr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  arch_phys_wc_add (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* drm_agp_init (struct drm_device*) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 

int i810_driver_load(struct drm_device *dev, unsigned long flags)
{
	dev->agp = drm_agp_init(dev);
	if (dev->agp) {
		dev->agp->agp_mtrr = arch_phys_wc_add(
			dev->agp->agp_info.aper_base,
			dev->agp->agp_info.aper_size *
			1024 * 1024);
	}

	/* Our userspace depends upon the agp mapping support. */
	if (!dev->agp)
		return -EINVAL;

	pci_set_master(dev->pdev);

	return 0;
}