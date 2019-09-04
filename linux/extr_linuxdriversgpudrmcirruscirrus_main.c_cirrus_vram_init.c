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
struct TYPE_4__ {int /*<<< orphan*/  vram_size; int /*<<< orphan*/  vram_base; } ;
struct cirrus_device {TYPE_2__ mc; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cirrus_vram_init(struct cirrus_device *cdev)
{
	/* BAR 0 is VRAM */
	cdev->mc.vram_base = pci_resource_start(cdev->dev->pdev, 0);
	cdev->mc.vram_size = pci_resource_len(cdev->dev->pdev, 0);

	if (!request_mem_region(cdev->mc.vram_base, cdev->mc.vram_size,
				"cirrusdrmfb_vram")) {
		DRM_ERROR("can't reserve VRAM\n");
		return -ENXIO;
	}

	return 0;
}