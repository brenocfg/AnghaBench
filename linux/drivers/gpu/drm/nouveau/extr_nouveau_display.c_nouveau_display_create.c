#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct nvkm_device {TYPE_1__* func; } ;
struct TYPE_20__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_14__ {scalar_t__ family; int chipset; } ;
struct TYPE_21__ {TYPE_2__ info; } ;
struct TYPE_17__ {TYPE_9__ device; } ;
struct TYPE_15__ {scalar_t__ entries; } ;
struct TYPE_16__ {TYPE_3__ dcb; } ;
struct nouveau_drm {TYPE_8__ acpi_nb; int /*<<< orphan*/  hpd_work; TYPE_5__ client; TYPE_4__ vbios; struct nouveau_display* display; } ;
struct TYPE_18__ {scalar_t__ oclass; } ;
struct TYPE_12__ {TYPE_6__ object; } ;
struct nouveau_display {int /*<<< orphan*/  (* dtor ) (struct drm_device*) ;TYPE_11__ disp; } ;
struct TYPE_19__ {int max_width; int max_height; int preferred_depth; int prefer_shadow; int async_page_flip; scalar_t__ num_crtc; scalar_t__ min_height; scalar_t__ min_width; int /*<<< orphan*/  fb_base; int /*<<< orphan*/ * funcs; } ;
struct drm_device {TYPE_7__ mode_config; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* resource_addr ) (struct nvkm_device*,int) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NV50_DISP ; 
 scalar_t__ NV_DEVICE_INFO_V0_CELSIUS ; 
 scalar_t__ NV_DEVICE_INFO_V0_FERMI ; 
 scalar_t__ NV_DEVICE_INFO_V0_TESLA ; 
 int /*<<< orphan*/  drm_kms_helper_poll_disable (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_create_dvi_i_properties (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_create_scaling_mode_property (struct drm_device*) ; 
 struct nouveau_display* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_display_acpi_ntfy ; 
 int /*<<< orphan*/  nouveau_display_create_properties (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_display_hpd_work ; 
 int nouveau_display_vblank_init (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_mode_config_funcs ; 
 int nouveau_modeset ; 
 int nv04_display_create (struct drm_device*) ; 
 int nv50_display_create (struct drm_device*) ; 
 int nvif_disp_ctor (TYPE_9__*,int /*<<< orphan*/ ,TYPE_11__*) ; 
 struct nvkm_device* nvxx_device (TYPE_9__*) ; 
 int /*<<< orphan*/  register_acpi_notifier (TYPE_8__*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct drm_device*) ; 

int
nouveau_display_create(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvkm_device *device = nvxx_device(&drm->client.device);
	struct nouveau_display *disp;
	int ret;

	disp = drm->display = kzalloc(sizeof(*disp), GFP_KERNEL);
	if (!disp)
		return -ENOMEM;

	drm_mode_config_init(dev);
	drm_mode_create_scaling_mode_property(dev);
	drm_mode_create_dvi_i_properties(dev);

	dev->mode_config.funcs = &nouveau_mode_config_funcs;
	dev->mode_config.fb_base = device->func->resource_addr(device, 1);

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	if (drm->client.device.info.family < NV_DEVICE_INFO_V0_CELSIUS) {
		dev->mode_config.max_width = 2048;
		dev->mode_config.max_height = 2048;
	} else
	if (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA) {
		dev->mode_config.max_width = 4096;
		dev->mode_config.max_height = 4096;
	} else
	if (drm->client.device.info.family < NV_DEVICE_INFO_V0_FERMI) {
		dev->mode_config.max_width = 8192;
		dev->mode_config.max_height = 8192;
	} else {
		dev->mode_config.max_width = 16384;
		dev->mode_config.max_height = 16384;
	}

	dev->mode_config.preferred_depth = 24;
	dev->mode_config.prefer_shadow = 1;

	if (drm->client.device.info.chipset < 0x11)
		dev->mode_config.async_page_flip = false;
	else
		dev->mode_config.async_page_flip = true;

	drm_kms_helper_poll_init(dev);
	drm_kms_helper_poll_disable(dev);

	if (nouveau_modeset != 2 && drm->vbios.dcb.entries) {
		ret = nvif_disp_ctor(&drm->client.device, 0, &disp->disp);
		if (ret == 0) {
			nouveau_display_create_properties(dev);
			if (disp->disp.object.oclass < NV50_DISP)
				ret = nv04_display_create(dev);
			else
				ret = nv50_display_create(dev);
		}
	} else {
		ret = 0;
	}

	if (ret)
		goto disp_create_err;

	drm_mode_config_reset(dev);

	if (dev->mode_config.num_crtc) {
		ret = nouveau_display_vblank_init(dev);
		if (ret)
			goto vblank_err;
	}

	INIT_WORK(&drm->hpd_work, nouveau_display_hpd_work);
#ifdef CONFIG_ACPI
	drm->acpi_nb.notifier_call = nouveau_display_acpi_ntfy;
	register_acpi_notifier(&drm->acpi_nb);
#endif

	return 0;

vblank_err:
	disp->dtor(dev);
disp_create_err:
	drm_kms_helper_poll_fini(dev);
	drm_mode_config_cleanup(dev);
	return ret;
}