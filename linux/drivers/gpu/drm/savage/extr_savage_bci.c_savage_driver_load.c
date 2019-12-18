#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_device {int /*<<< orphan*/  pdev; void* dev_private; } ;
typedef  enum savage_family { ____Placeholder_savage_family } savage_family ;
struct TYPE_3__ {int chipset; } ;
typedef  TYPE_1__ drm_savage_private_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 

int savage_driver_load(struct drm_device *dev, unsigned long chipset)
{
	drm_savage_private_t *dev_priv;

	dev_priv = kzalloc(sizeof(drm_savage_private_t), GFP_KERNEL);
	if (dev_priv == NULL)
		return -ENOMEM;

	dev->dev_private = (void *)dev_priv;

	dev_priv->chipset = (enum savage_family)chipset;

	pci_set_master(dev->pdev);

	return 0;
}