#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_device {int irq_enabled; struct komeda_dev* dev_private; TYPE_1__* driver; int /*<<< orphan*/  dev; } ;
struct komeda_kms_dev {int /*<<< orphan*/  n_crtcs; struct drm_device base; } ;
struct komeda_dev {int /*<<< orphan*/  dev; TYPE_2__* funcs; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int (* enable_irq ) (struct komeda_dev*) ;int /*<<< orphan*/  (* disable_irq ) (struct komeda_dev*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct komeda_kms_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int component_bind_all (int /*<<< orphan*/ ,struct komeda_kms_dev*) ; 
 int /*<<< orphan*/  component_unbind_all (int /*<<< orphan*/ ,struct drm_device*) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_device*) ; 
 int drm_dev_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int drm_vblank_init (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct komeda_kms_dev*) ; 
 int komeda_kms_add_crtcs (struct komeda_kms_dev*,struct komeda_dev*) ; 
 int komeda_kms_add_planes (struct komeda_kms_dev*,struct komeda_dev*) ; 
 int komeda_kms_add_private_objs (struct komeda_kms_dev*,struct komeda_dev*) ; 
 int komeda_kms_add_wb_connectors (struct komeda_kms_dev*,struct komeda_dev*) ; 
 int /*<<< orphan*/  komeda_kms_cleanup_private_objs (struct komeda_kms_dev*) ; 
 int /*<<< orphan*/  komeda_kms_driver ; 
 int /*<<< orphan*/  komeda_kms_irq_handler ; 
 int /*<<< orphan*/  komeda_kms_mode_config_init (struct komeda_kms_dev*,struct komeda_dev*) ; 
 struct komeda_kms_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct komeda_dev*) ; 
 int /*<<< orphan*/  stub2 (struct komeda_dev*) ; 

struct komeda_kms_dev *komeda_kms_attach(struct komeda_dev *mdev)
{
	struct komeda_kms_dev *kms = kzalloc(sizeof(*kms), GFP_KERNEL);
	struct drm_device *drm;
	int err;

	if (!kms)
		return ERR_PTR(-ENOMEM);

	drm = &kms->base;
	err = drm_dev_init(drm, &komeda_kms_driver, mdev->dev);
	if (err)
		goto free_kms;

	drm->dev_private = mdev;

	komeda_kms_mode_config_init(kms, mdev);

	err = komeda_kms_add_private_objs(kms, mdev);
	if (err)
		goto cleanup_mode_config;

	err = komeda_kms_add_planes(kms, mdev);
	if (err)
		goto cleanup_mode_config;

	err = drm_vblank_init(drm, kms->n_crtcs);
	if (err)
		goto cleanup_mode_config;

	err = komeda_kms_add_crtcs(kms, mdev);
	if (err)
		goto cleanup_mode_config;

	err = komeda_kms_add_wb_connectors(kms, mdev);
	if (err)
		goto cleanup_mode_config;

	err = component_bind_all(mdev->dev, kms);
	if (err)
		goto cleanup_mode_config;

	drm_mode_config_reset(drm);

	err = devm_request_irq(drm->dev, mdev->irq,
			       komeda_kms_irq_handler, IRQF_SHARED,
			       drm->driver->name, drm);
	if (err)
		goto free_component_binding;

	err = mdev->funcs->enable_irq(mdev);
	if (err)
		goto free_component_binding;

	drm->irq_enabled = true;

	drm_kms_helper_poll_init(drm);

	err = drm_dev_register(drm, 0);
	if (err)
		goto free_interrupts;

	return kms;

free_interrupts:
	drm_kms_helper_poll_fini(drm);
	drm->irq_enabled = false;
	mdev->funcs->disable_irq(mdev);
free_component_binding:
	component_unbind_all(mdev->dev, drm);
cleanup_mode_config:
	drm_mode_config_cleanup(drm);
	komeda_kms_cleanup_private_objs(kms);
	drm->dev_private = NULL;
	drm_dev_put(drm);
free_kms:
	kfree(kms);
	return ERR_PTR(err);
}