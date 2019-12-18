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
struct nouveau_display {int /*<<< orphan*/  disp; int /*<<< orphan*/  (* dtor ) (struct drm_device*) ;} ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * display; int /*<<< orphan*/  acpi_nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (struct nouveau_display*) ; 
 struct nouveau_display* nouveau_display (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_display_vblank_fini (struct drm_device*) ; 
 TYPE_1__* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nvif_disp_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 
 int /*<<< orphan*/  unregister_acpi_notifier (int /*<<< orphan*/ *) ; 

void
nouveau_display_destroy(struct drm_device *dev)
{
	struct nouveau_display *disp = nouveau_display(dev);

#ifdef CONFIG_ACPI
	unregister_acpi_notifier(&nouveau_drm(dev)->acpi_nb);
#endif
	nouveau_display_vblank_fini(dev);

	drm_kms_helper_poll_fini(dev);
	drm_mode_config_cleanup(dev);

	if (disp->dtor)
		disp->dtor(dev);

	nvif_disp_dtor(&disp->disp);

	nouveau_drm(dev)->display = NULL;
	kfree(disp);
}