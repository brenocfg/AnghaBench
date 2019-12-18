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
struct exynos_drm_ipp {int dummy; } ;
struct gsc_context {struct exynos_drm_ipp ipp; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct gsc_context* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  exynos_drm_ipp_unregister (struct device*,struct exynos_drm_ipp*) ; 
 int /*<<< orphan*/  exynos_drm_unregister_dma (struct drm_device*,struct device*) ; 

__attribute__((used)) static void gsc_unbind(struct device *dev, struct device *master,
			void *data)
{
	struct gsc_context *ctx = dev_get_drvdata(dev);
	struct drm_device *drm_dev = data;
	struct exynos_drm_ipp *ipp = &ctx->ipp;

	exynos_drm_ipp_unregister(dev, ipp);
	exynos_drm_unregister_dma(drm_dev, dev);
}