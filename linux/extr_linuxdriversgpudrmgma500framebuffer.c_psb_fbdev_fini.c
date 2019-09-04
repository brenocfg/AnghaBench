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
struct drm_psb_private {int /*<<< orphan*/ * fbdev; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psb_fbdev_destroy (struct drm_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void psb_fbdev_fini(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;

	if (!dev_priv->fbdev)
		return;

	psb_fbdev_destroy(dev, dev_priv->fbdev);
	kfree(dev_priv->fbdev);
	dev_priv->fbdev = NULL;
}