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
struct drm_encoder {TYPE_1__* funcs; } ;
struct TYPE_4__ {struct drm_encoder* encoder; int /*<<< orphan*/  panel; int /*<<< orphan*/  get_modes; int /*<<< orphan*/  attach; int /*<<< orphan*/  power_off; int /*<<< orphan*/  power_on_start; int /*<<< orphan*/  dev_type; } ;
struct exynos_dp_device {int /*<<< orphan*/  adp; struct drm_encoder encoder; TYPE_2__ plat_data; struct drm_device* drm_dev; int /*<<< orphan*/  ptn_bridge; struct device* dev; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy ) (struct drm_encoder*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  EXYNOS_DISPLAY_TYPE_LCD ; 
 int /*<<< orphan*/  EXYNOS_DP ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  analogix_dp_bind (struct device*,struct drm_device*,TYPE_2__*) ; 
 struct exynos_dp_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exynos_dp_bridge_attach ; 
 int exynos_dp_dt_parse_panel (struct exynos_dp_device*) ; 
 int /*<<< orphan*/  exynos_dp_encoder_funcs ; 
 int /*<<< orphan*/  exynos_dp_encoder_helper_funcs ; 
 int /*<<< orphan*/  exynos_dp_get_modes ; 
 int /*<<< orphan*/  exynos_dp_poweroff ; 
 int /*<<< orphan*/  exynos_dp_poweron ; 
 int exynos_drm_set_possible_crtcs (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*) ; 

__attribute__((used)) static int exynos_dp_bind(struct device *dev, struct device *master, void *data)
{
	struct exynos_dp_device *dp = dev_get_drvdata(dev);
	struct drm_encoder *encoder = &dp->encoder;
	struct drm_device *drm_dev = data;
	int ret;

	dp->dev = dev;
	dp->drm_dev = drm_dev;

	dp->plat_data.dev_type = EXYNOS_DP;
	dp->plat_data.power_on_start = exynos_dp_poweron;
	dp->plat_data.power_off = exynos_dp_poweroff;
	dp->plat_data.attach = exynos_dp_bridge_attach;
	dp->plat_data.get_modes = exynos_dp_get_modes;

	if (!dp->plat_data.panel && !dp->ptn_bridge) {
		ret = exynos_dp_dt_parse_panel(dp);
		if (ret)
			return ret;
	}

	drm_encoder_init(drm_dev, encoder, &exynos_dp_encoder_funcs,
			 DRM_MODE_ENCODER_TMDS, NULL);

	drm_encoder_helper_add(encoder, &exynos_dp_encoder_helper_funcs);

	ret = exynos_drm_set_possible_crtcs(encoder, EXYNOS_DISPLAY_TYPE_LCD);
	if (ret < 0)
		return ret;

	dp->plat_data.encoder = encoder;

	dp->adp = analogix_dp_bind(dev, dp->drm_dev, &dp->plat_data);
	if (IS_ERR(dp->adp)) {
		dp->encoder.funcs->destroy(&dp->encoder);
		return PTR_ERR(dp->adp);
	}

	return 0;
}