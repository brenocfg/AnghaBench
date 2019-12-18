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
struct scaler_context {int /*<<< orphan*/  dev; int /*<<< orphan*/  drm_dev; struct exynos_drm_ipp ipp; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct scaler_context* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  exynos_drm_ipp_unregister (struct device*,struct exynos_drm_ipp*) ; 
 int /*<<< orphan*/  exynos_drm_unregister_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scaler_unbind(struct device *dev, struct device *master,
			void *data)
{
	struct scaler_context *scaler = dev_get_drvdata(dev);
	struct exynos_drm_ipp *ipp = &scaler->ipp;

	exynos_drm_ipp_unregister(dev, ipp);
	exynos_drm_unregister_dma(scaler->drm_dev, scaler->dev);
}