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
struct exynos_dsi {int /*<<< orphan*/  dsi_host; scalar_t__ in_bridge_node; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_bridge {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  EXYNOS_DISPLAY_TYPE_LCD ; 
 struct drm_encoder* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_bridge_attach (struct drm_encoder*,struct drm_bridge*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct exynos_dsi* encoder_to_dsi (struct drm_encoder*) ; 
 int exynos_drm_set_possible_crtcs (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_dsi_encoder_funcs ; 
 int /*<<< orphan*/  exynos_dsi_encoder_helper_funcs ; 
 int mipi_dsi_host_register (int /*<<< orphan*/ *) ; 
 struct drm_bridge* of_drm_find_bridge (scalar_t__) ; 

__attribute__((used)) static int exynos_dsi_bind(struct device *dev, struct device *master,
				void *data)
{
	struct drm_encoder *encoder = dev_get_drvdata(dev);
	struct exynos_dsi *dsi = encoder_to_dsi(encoder);
	struct drm_device *drm_dev = data;
	struct drm_bridge *in_bridge;
	int ret;

	drm_encoder_init(drm_dev, encoder, &exynos_dsi_encoder_funcs,
			 DRM_MODE_ENCODER_TMDS, NULL);

	drm_encoder_helper_add(encoder, &exynos_dsi_encoder_helper_funcs);

	ret = exynos_drm_set_possible_crtcs(encoder, EXYNOS_DISPLAY_TYPE_LCD);
	if (ret < 0)
		return ret;

	if (dsi->in_bridge_node) {
		in_bridge = of_drm_find_bridge(dsi->in_bridge_node);
		if (in_bridge)
			drm_bridge_attach(encoder, in_bridge, NULL);
	}

	return mipi_dsi_host_register(&dsi->dsi_host);
}