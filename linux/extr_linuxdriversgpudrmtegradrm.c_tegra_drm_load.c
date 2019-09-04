#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
struct TYPE_6__ {unsigned long shift; unsigned long limit; int /*<<< orphan*/  domain; } ;
struct tegra_drm {TYPE_3__* domain; TYPE_2__ carveout; int /*<<< orphan*/  mm; int /*<<< orphan*/  mm_lock; scalar_t__ hub; struct drm_device* drm; int /*<<< orphan*/  clients; int /*<<< orphan*/  clients_lock; } ;
struct iommu_domain_geometry {unsigned long aperture_start; unsigned long aperture_end; } ;
struct host1x_device {int dummy; } ;
struct TYPE_5__ {int max_width; int max_height; int allow_fb_modifiers; int normalize_zpos; int /*<<< orphan*/  num_crtc; int /*<<< orphan*/ * helper_private; int /*<<< orphan*/ * funcs; scalar_t__ min_height; scalar_t__ min_width; } ;
struct drm_device {int irq_enabled; int max_vblank_count; TYPE_1__ mode_config; struct tegra_drm* dev_private; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  pgsize_bitmap; struct iommu_domain_geometry geometry; } ;

/* Variables and functions */
 unsigned long CARVEOUT_SZ ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned long __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int drm_vblank_init (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_device_exit (struct host1x_device*) ; 
 int host1x_device_init (struct host1x_device*) ; 
 int /*<<< orphan*/  init_iova_domain (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 TYPE_3__* iommu_domain_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_domain_free (TYPE_3__*) ; 
 scalar_t__ iommu_present (int /*<<< orphan*/ *) ; 
 int iova_cache_get () ; 
 int /*<<< orphan*/  iova_cache_put () ; 
 unsigned long iova_shift (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tegra_drm*) ; 
 struct tegra_drm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int /*<<< orphan*/  put_iova_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_display_hub_cleanup (scalar_t__) ; 
 int tegra_display_hub_prepare (scalar_t__) ; 
 int /*<<< orphan*/  tegra_drm_fb_free (struct drm_device*) ; 
 int tegra_drm_fb_init (struct drm_device*) ; 
 int tegra_drm_fb_prepare (struct drm_device*) ; 
 int /*<<< orphan*/  tegra_drm_mode_config_funcs ; 
 int /*<<< orphan*/  tegra_drm_mode_config_helpers ; 
 struct host1x_device* to_host1x_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_drm_load(struct drm_device *drm, unsigned long flags)
{
	struct host1x_device *device = to_host1x_device(drm->dev);
	struct tegra_drm *tegra;
	int err;

	tegra = kzalloc(sizeof(*tegra), GFP_KERNEL);
	if (!tegra)
		return -ENOMEM;

	if (iommu_present(&platform_bus_type)) {
		u64 carveout_start, carveout_end, gem_start, gem_end;
		struct iommu_domain_geometry *geometry;
		unsigned long order;

		tegra->domain = iommu_domain_alloc(&platform_bus_type);
		if (!tegra->domain) {
			err = -ENOMEM;
			goto free;
		}

		err = iova_cache_get();
		if (err < 0)
			goto domain;

		geometry = &tegra->domain->geometry;
		gem_start = geometry->aperture_start;
		gem_end = geometry->aperture_end - CARVEOUT_SZ;
		carveout_start = gem_end + 1;
		carveout_end = geometry->aperture_end;

		order = __ffs(tegra->domain->pgsize_bitmap);
		init_iova_domain(&tegra->carveout.domain, 1UL << order,
				 carveout_start >> order);

		tegra->carveout.shift = iova_shift(&tegra->carveout.domain);
		tegra->carveout.limit = carveout_end >> tegra->carveout.shift;

		drm_mm_init(&tegra->mm, gem_start, gem_end - gem_start + 1);
		mutex_init(&tegra->mm_lock);

		DRM_DEBUG("IOMMU apertures:\n");
		DRM_DEBUG("  GEM: %#llx-%#llx\n", gem_start, gem_end);
		DRM_DEBUG("  Carveout: %#llx-%#llx\n", carveout_start,
			  carveout_end);
	}

	mutex_init(&tegra->clients_lock);
	INIT_LIST_HEAD(&tegra->clients);

	drm->dev_private = tegra;
	tegra->drm = drm;

	drm_mode_config_init(drm);

	drm->mode_config.min_width = 0;
	drm->mode_config.min_height = 0;

	drm->mode_config.max_width = 4096;
	drm->mode_config.max_height = 4096;

	drm->mode_config.allow_fb_modifiers = true;

	drm->mode_config.normalize_zpos = true;

	drm->mode_config.funcs = &tegra_drm_mode_config_funcs;
	drm->mode_config.helper_private = &tegra_drm_mode_config_helpers;

	err = tegra_drm_fb_prepare(drm);
	if (err < 0)
		goto config;

	drm_kms_helper_poll_init(drm);

	err = host1x_device_init(device);
	if (err < 0)
		goto fbdev;

	if (tegra->hub) {
		err = tegra_display_hub_prepare(tegra->hub);
		if (err < 0)
			goto device;
	}

	/*
	 * We don't use the drm_irq_install() helpers provided by the DRM
	 * core, so we need to set this manually in order to allow the
	 * DRM_IOCTL_WAIT_VBLANK to operate correctly.
	 */
	drm->irq_enabled = true;

	/* syncpoints are used for full 32-bit hardware VBLANK counters */
	drm->max_vblank_count = 0xffffffff;

	err = drm_vblank_init(drm, drm->mode_config.num_crtc);
	if (err < 0)
		goto hub;

	drm_mode_config_reset(drm);

	err = tegra_drm_fb_init(drm);
	if (err < 0)
		goto hub;

	return 0;

hub:
	if (tegra->hub)
		tegra_display_hub_cleanup(tegra->hub);
device:
	host1x_device_exit(device);
fbdev:
	drm_kms_helper_poll_fini(drm);
	tegra_drm_fb_free(drm);
config:
	drm_mode_config_cleanup(drm);

	if (tegra->domain) {
		mutex_destroy(&tegra->mm_lock);
		drm_mm_takedown(&tegra->mm);
		put_iova_domain(&tegra->carveout.domain);
		iova_cache_put();
	}
domain:
	if (tegra->domain)
		iommu_domain_free(tegra->domain);
free:
	kfree(tegra);
	return err;
}