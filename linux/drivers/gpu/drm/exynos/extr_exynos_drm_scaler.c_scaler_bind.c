#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct exynos_drm_ipp {struct drm_device* drm_dev; } ;
struct scaler_context {TYPE_1__* scaler_data; struct drm_device* drm_dev; struct exynos_drm_ipp ipp; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_formats; int /*<<< orphan*/  formats; } ;

/* Variables and functions */
 int DRM_EXYNOS_IPP_CAP_CONVERT ; 
 int DRM_EXYNOS_IPP_CAP_CROP ; 
 int DRM_EXYNOS_IPP_CAP_ROTATE ; 
 int DRM_EXYNOS_IPP_CAP_SCALE ; 
 struct scaler_context* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  exynos_drm_ipp_register (struct device*,struct exynos_drm_ipp*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exynos_drm_register_dma (struct drm_device*,struct device*) ; 
 int /*<<< orphan*/  ipp_funcs ; 

__attribute__((used)) static int scaler_bind(struct device *dev, struct device *master, void *data)
{
	struct scaler_context *scaler = dev_get_drvdata(dev);
	struct drm_device *drm_dev = data;
	struct exynos_drm_ipp *ipp = &scaler->ipp;

	scaler->drm_dev = drm_dev;
	ipp->drm_dev = drm_dev;
	exynos_drm_register_dma(drm_dev, dev);

	exynos_drm_ipp_register(dev, ipp, &ipp_funcs,
			DRM_EXYNOS_IPP_CAP_CROP | DRM_EXYNOS_IPP_CAP_ROTATE |
			DRM_EXYNOS_IPP_CAP_SCALE | DRM_EXYNOS_IPP_CAP_CONVERT,
			scaler->scaler_data->formats,
			scaler->scaler_data->num_formats, "scaler");

	dev_info(dev, "The exynos scaler has been probed successfully\n");

	return 0;
}