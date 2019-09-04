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
struct exynos_drm_private {struct device* dma_dev; } ;
struct drm_device {struct exynos_drm_private* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct device *to_dma_dev(struct drm_device *dev)
{
	struct exynos_drm_private *priv = dev->dev_private;

	return priv->dma_dev;
}