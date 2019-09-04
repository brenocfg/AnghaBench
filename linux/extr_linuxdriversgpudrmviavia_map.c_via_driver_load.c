#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_device {int /*<<< orphan*/  pdev; void* dev_private; } ;
struct TYPE_4__ {unsigned long chipset; int /*<<< orphan*/  object_idr; } ;
typedef  TYPE_1__ drm_via_private_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int drm_vblank_init (struct drm_device*,int) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 

int via_driver_load(struct drm_device *dev, unsigned long chipset)
{
	drm_via_private_t *dev_priv;
	int ret = 0;

	dev_priv = kzalloc(sizeof(drm_via_private_t), GFP_KERNEL);
	if (dev_priv == NULL)
		return -ENOMEM;

	idr_init(&dev_priv->object_idr);
	dev->dev_private = (void *)dev_priv;

	dev_priv->chipset = chipset;

	pci_set_master(dev->pdev);

	ret = drm_vblank_init(dev, 1);
	if (ret) {
		kfree(dev_priv);
		return ret;
	}

	return 0;
}