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
struct tilcdc_drm_private {int /*<<< orphan*/  clk; } ;
struct tilcdc_crtc {scalar_t__ lcd_fck_rate; } ;
struct drm_device {int /*<<< orphan*/  dev; struct tilcdc_drm_private* dev_private; } ;
struct drm_crtc {int /*<<< orphan*/  mutex; struct drm_device* dev; } ;

/* Variables and functions */
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tilcdc_crtc_disable (struct drm_crtc*) ; 
 int /*<<< orphan*/  tilcdc_crtc_enable (struct drm_crtc*) ; 
 scalar_t__ tilcdc_crtc_is_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  tilcdc_crtc_set_clk (struct drm_crtc*) ; 
 struct tilcdc_crtc* to_tilcdc_crtc (struct drm_crtc*) ; 

void tilcdc_crtc_update_clk(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct tilcdc_drm_private *priv = dev->dev_private;
	struct tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);

	drm_modeset_lock(&crtc->mutex, NULL);
	if (tilcdc_crtc->lcd_fck_rate != clk_get_rate(priv->clk)) {
		if (tilcdc_crtc_is_on(crtc)) {
			pm_runtime_get_sync(dev->dev);
			tilcdc_crtc_disable(crtc);

			tilcdc_crtc_set_clk(crtc);

			tilcdc_crtc_enable(crtc);
			pm_runtime_put_sync(dev->dev);
		}
	}
	drm_modeset_unlock(&crtc->mutex);
}