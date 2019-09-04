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
struct etnaviv_drm_private {int dummy; } ;
struct drm_device {struct etnaviv_drm_private* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_unbind_all (struct device*,struct drm_device*) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_dev_unref (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (struct etnaviv_drm_private*) ; 

__attribute__((used)) static void etnaviv_unbind(struct device *dev)
{
	struct drm_device *drm = dev_get_drvdata(dev);
	struct etnaviv_drm_private *priv = drm->dev_private;

	drm_dev_unregister(drm);

	component_unbind_all(dev, drm);

	drm->dev_private = NULL;
	kfree(priv);

	drm_dev_unref(drm);
}