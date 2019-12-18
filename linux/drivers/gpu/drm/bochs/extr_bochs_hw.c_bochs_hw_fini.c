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
struct drm_device {int /*<<< orphan*/  pdev; struct bochs_device* dev_private; } ;
struct bochs_device {int /*<<< orphan*/  edid; scalar_t__ fb_map; scalar_t__ ioports; scalar_t__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  VBE_DISPI_IOPORT_INDEX ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 

void bochs_hw_fini(struct drm_device *dev)
{
	struct bochs_device *bochs = dev->dev_private;

	if (bochs->mmio)
		iounmap(bochs->mmio);
	if (bochs->ioports)
		release_region(VBE_DISPI_IOPORT_INDEX, 2);
	if (bochs->fb_map)
		iounmap(bochs->fb_map);
	pci_release_regions(dev->pdev);
	kfree(bochs->edid);
}