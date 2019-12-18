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
struct meson_drm {int /*<<< orphan*/  canvas_id_vd1_2; scalar_t__ canvas; int /*<<< orphan*/  canvas_id_vd1_1; int /*<<< orphan*/  canvas_id_vd1_0; int /*<<< orphan*/  canvas_id_osd1; struct drm_device* drm; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct meson_drm* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  meson_canvas_free (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson_drv_unbind(struct device *dev)
{
	struct meson_drm *priv = dev_get_drvdata(dev);
	struct drm_device *drm = priv->drm;

	if (priv->canvas) {
		meson_canvas_free(priv->canvas, priv->canvas_id_osd1);
		meson_canvas_free(priv->canvas, priv->canvas_id_vd1_0);
		meson_canvas_free(priv->canvas, priv->canvas_id_vd1_1);
		meson_canvas_free(priv->canvas, priv->canvas_id_vd1_2);
	}

	drm_dev_unregister(drm);
	drm_irq_uninstall(drm);
	drm_kms_helper_poll_fini(drm);
	drm_mode_config_cleanup(drm);
	drm_dev_put(drm);

}