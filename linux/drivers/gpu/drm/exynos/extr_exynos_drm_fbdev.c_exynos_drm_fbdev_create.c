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
struct exynos_drm_gem {int dummy; } ;
struct exynos_drm_fbdev {struct exynos_drm_gem* exynos_gem; } ;
struct drm_mode_fb_cmd2 {int width; unsigned long height; int* pitches; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  member_0; } ;
struct drm_fb_helper_surface_size {int surface_width; unsigned long surface_height; int surface_bpp; int /*<<< orphan*/  surface_depth; } ;
struct drm_fb_helper {struct exynos_drm_gem* fb; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int,unsigned long,int) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EXYNOS_BO_CONTIG ; 
 int /*<<< orphan*/  EXYNOS_BO_NONCONTIG ; 
 scalar_t__ IS_ERR (struct exynos_drm_gem*) ; 
 int PTR_ERR (struct exynos_drm_gem*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (struct exynos_drm_gem*) ; 
 int /*<<< orphan*/  drm_mode_legacy_fb_format (int,int /*<<< orphan*/ ) ; 
 int exynos_drm_fbdev_update (struct drm_fb_helper*,struct drm_fb_helper_surface_size*,struct exynos_drm_gem*) ; 
 struct exynos_drm_gem* exynos_drm_framebuffer_init (struct drm_device*,struct drm_mode_fb_cmd2*,struct exynos_drm_gem**,int) ; 
 struct exynos_drm_gem* exynos_drm_gem_create (struct drm_device*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  exynos_drm_gem_destroy (struct exynos_drm_gem*) ; 
 scalar_t__ is_drm_iommu_supported (struct drm_device*) ; 
 struct exynos_drm_fbdev* to_exynos_fbdev (struct drm_fb_helper*) ; 

__attribute__((used)) static int exynos_drm_fbdev_create(struct drm_fb_helper *helper,
				    struct drm_fb_helper_surface_size *sizes)
{
	struct exynos_drm_fbdev *exynos_fbdev = to_exynos_fbdev(helper);
	struct exynos_drm_gem *exynos_gem;
	struct drm_device *dev = helper->dev;
	struct drm_mode_fb_cmd2 mode_cmd = { 0 };
	unsigned long size;
	int ret;

	DRM_DEV_DEBUG_KMS(dev->dev,
			  "surface width(%d), height(%d) and bpp(%d\n",
			  sizes->surface_width, sizes->surface_height,
			  sizes->surface_bpp);

	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;
	mode_cmd.pitches[0] = sizes->surface_width * (sizes->surface_bpp >> 3);
	mode_cmd.pixel_format = drm_mode_legacy_fb_format(sizes->surface_bpp,
							  sizes->surface_depth);

	size = mode_cmd.pitches[0] * mode_cmd.height;

	exynos_gem = exynos_drm_gem_create(dev, EXYNOS_BO_CONTIG, size);
	/*
	 * If physically contiguous memory allocation fails and if IOMMU is
	 * supported then try to get buffer from non physically contiguous
	 * memory area.
	 */
	if (IS_ERR(exynos_gem) && is_drm_iommu_supported(dev)) {
		dev_warn(dev->dev, "contiguous FB allocation failed, falling back to non-contiguous\n");
		exynos_gem = exynos_drm_gem_create(dev, EXYNOS_BO_NONCONTIG,
						   size);
	}

	if (IS_ERR(exynos_gem))
		return PTR_ERR(exynos_gem);

	exynos_fbdev->exynos_gem = exynos_gem;

	helper->fb =
		exynos_drm_framebuffer_init(dev, &mode_cmd, &exynos_gem, 1);
	if (IS_ERR(helper->fb)) {
		DRM_DEV_ERROR(dev->dev, "failed to create drm framebuffer.\n");
		ret = PTR_ERR(helper->fb);
		goto err_destroy_gem;
	}

	ret = exynos_drm_fbdev_update(helper, sizes, exynos_gem);
	if (ret < 0)
		goto err_destroy_framebuffer;

	return ret;

err_destroy_framebuffer:
	drm_framebuffer_cleanup(helper->fb);
err_destroy_gem:
	exynos_drm_gem_destroy(exynos_gem);

	/*
	 * if failed, all resources allocated above would be released by
	 * drm_mode_config_cleanup() when drm_load() had been called prior
	 * to any specific driver such as fimd or hdmi driver.
	 */

	return ret;
}