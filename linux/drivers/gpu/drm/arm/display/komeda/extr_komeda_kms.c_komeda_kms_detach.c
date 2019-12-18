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
struct drm_device {int irq_enabled; struct komeda_dev* dev_private; } ;
struct komeda_kms_dev {struct drm_device base; } ;
struct komeda_dev {int /*<<< orphan*/  dev; TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_irq ) (struct komeda_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  component_unbind_all (int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  drm_atomic_helper_shutdown (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  komeda_kms_cleanup_private_objs (struct komeda_kms_dev*) ; 
 int /*<<< orphan*/  stub1 (struct komeda_dev*) ; 

void komeda_kms_detach(struct komeda_kms_dev *kms)
{
	struct drm_device *drm = &kms->base;
	struct komeda_dev *mdev = drm->dev_private;

	drm_dev_unregister(drm);
	drm_kms_helper_poll_fini(drm);
	drm_atomic_helper_shutdown(drm);
	drm->irq_enabled = false;
	mdev->funcs->disable_irq(mdev);
	component_unbind_all(mdev->dev, drm);
	drm_mode_config_cleanup(drm);
	komeda_kms_cleanup_private_objs(kms);
	drm->dev_private = NULL;
	drm_dev_put(drm);
}