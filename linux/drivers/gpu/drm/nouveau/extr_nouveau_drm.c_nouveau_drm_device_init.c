#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int chipset; } ;
struct TYPE_10__ {int /*<<< orphan*/  object; TYPE_2__ info; } ;
struct TYPE_13__ {TYPE_3__ device; int /*<<< orphan*/  base; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct nouveau_drm {TYPE_6__ master; TYPE_6__ client; TYPE_1__ tile; int /*<<< orphan*/  clients; struct drm_device* dev; } ;
struct TYPE_11__ {scalar_t__ num_crtc; } ;
struct drm_device {int irq_enabled; int /*<<< orphan*/  dev; TYPE_4__ mode_config; struct nouveau_drm* dev_private; } ;
struct TYPE_12__ {int /*<<< orphan*/  debug; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nouveau_drm*) ; 
 struct nouveau_drm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_accel_fini (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nouveau_accel_init (struct nouveau_drm*) ; 
 int nouveau_bios_init (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_bios_takedown (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_cli_fini (TYPE_6__*) ; 
 int nouveau_cli_init (struct nouveau_drm*,char*,TYPE_6__*) ; 
 int /*<<< orphan*/  nouveau_debug ; 
 int /*<<< orphan*/  nouveau_debugfs_init (struct nouveau_drm*) ; 
 int nouveau_display_create (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_display_destroy (struct drm_device*) ; 
 int nouveau_display_init (struct drm_device*,int,int) ; 
 int /*<<< orphan*/  nouveau_dmem_init (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nouveau_fbcon_init (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_hwmon_init (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_led_init (struct drm_device*) ; 
 scalar_t__ nouveau_pmops_runtime () ; 
 int /*<<< orphan*/  nouveau_svm_init (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nouveau_ttm_fini (struct nouveau_drm*) ; 
 int nouveau_ttm_init (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nouveau_vga_fini (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nouveau_vga_init (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nvif_mask (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  nvkm_dbgopt (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* nvxx_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nouveau_drm_device_init(struct drm_device *dev)
{
	struct nouveau_drm *drm;
	int ret;

	if (!(drm = kzalloc(sizeof(*drm), GFP_KERNEL)))
		return -ENOMEM;
	dev->dev_private = drm;
	drm->dev = dev;

	ret = nouveau_cli_init(drm, "DRM-master", &drm->master);
	if (ret)
		goto fail_alloc;

	ret = nouveau_cli_init(drm, "DRM", &drm->client);
	if (ret)
		goto fail_master;

	dev->irq_enabled = true;

	nvxx_client(&drm->client.base)->debug =
		nvkm_dbgopt(nouveau_debug, "DRM");

	INIT_LIST_HEAD(&drm->clients);
	spin_lock_init(&drm->tile.lock);

	/* workaround an odd issue on nvc1 by disabling the device's
	 * nosnoop capability.  hopefully won't cause issues until a
	 * better fix is found - assuming there is one...
	 */
	if (drm->client.device.info.chipset == 0xc1)
		nvif_mask(&drm->client.device.object, 0x00088080, 0x00000800, 0x00000000);

	nouveau_vga_init(drm);

	ret = nouveau_ttm_init(drm);
	if (ret)
		goto fail_ttm;

	ret = nouveau_bios_init(dev);
	if (ret)
		goto fail_bios;

	nouveau_accel_init(drm);

	ret = nouveau_display_create(dev);
	if (ret)
		goto fail_dispctor;

	if (dev->mode_config.num_crtc) {
		ret = nouveau_display_init(dev, false, false);
		if (ret)
			goto fail_dispinit;
	}

	nouveau_debugfs_init(drm);
	nouveau_hwmon_init(dev);
	nouveau_svm_init(drm);
	nouveau_dmem_init(drm);
	nouveau_fbcon_init(dev);
	nouveau_led_init(dev);

	if (nouveau_pmops_runtime()) {
		pm_runtime_use_autosuspend(dev->dev);
		pm_runtime_set_autosuspend_delay(dev->dev, 5000);
		pm_runtime_set_active(dev->dev);
		pm_runtime_allow(dev->dev);
		pm_runtime_mark_last_busy(dev->dev);
		pm_runtime_put(dev->dev);
	}

	return 0;

fail_dispinit:
	nouveau_display_destroy(dev);
fail_dispctor:
	nouveau_accel_fini(drm);
	nouveau_bios_takedown(dev);
fail_bios:
	nouveau_ttm_fini(drm);
fail_ttm:
	nouveau_vga_fini(drm);
	nouveau_cli_fini(&drm->client);
fail_master:
	nouveau_cli_fini(&drm->master);
fail_alloc:
	kfree(drm);
	return ret;
}