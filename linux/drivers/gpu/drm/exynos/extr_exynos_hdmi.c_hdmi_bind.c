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
struct TYPE_2__ {int /*<<< orphan*/  enable; } ;
struct drm_encoder {int dummy; } ;
struct hdmi_context {TYPE_1__ phy_clk; struct drm_device* drm_dev; struct drm_encoder encoder; } ;
struct exynos_drm_crtc {TYPE_1__* pipe_clk; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  EXYNOS_DISPLAY_TYPE_HDMI ; 
 struct hdmi_context* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct exynos_drm_crtc* exynos_drm_crtc_get_by_type (struct drm_device*,int /*<<< orphan*/ ) ; 
 int exynos_drm_set_possible_crtcs (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_hdmi_encoder_funcs ; 
 int /*<<< orphan*/  exynos_hdmi_encoder_helper_funcs ; 
 int hdmi_create_connector (struct drm_encoder*) ; 
 int /*<<< orphan*/  hdmiphy_clk_enable ; 

__attribute__((used)) static int hdmi_bind(struct device *dev, struct device *master, void *data)
{
	struct drm_device *drm_dev = data;
	struct hdmi_context *hdata = dev_get_drvdata(dev);
	struct drm_encoder *encoder = &hdata->encoder;
	struct exynos_drm_crtc *crtc;
	int ret;

	hdata->drm_dev = drm_dev;

	hdata->phy_clk.enable = hdmiphy_clk_enable;

	drm_encoder_init(drm_dev, encoder, &exynos_hdmi_encoder_funcs,
			 DRM_MODE_ENCODER_TMDS, NULL);

	drm_encoder_helper_add(encoder, &exynos_hdmi_encoder_helper_funcs);

	ret = exynos_drm_set_possible_crtcs(encoder, EXYNOS_DISPLAY_TYPE_HDMI);
	if (ret < 0)
		return ret;

	crtc = exynos_drm_crtc_get_by_type(drm_dev, EXYNOS_DISPLAY_TYPE_HDMI);
	crtc->pipe_clk = &hdata->phy_clk;

	ret = hdmi_create_connector(encoder);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to create connector ret = %d\n",
			      ret);
		drm_encoder_cleanup(encoder);
		return ret;
	}

	return 0;
}