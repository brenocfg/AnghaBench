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
struct rockchip_lvds {int /*<<< orphan*/  panel; int /*<<< orphan*/  dev; } ;
struct drm_encoder {TYPE_2__* crtc; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* state; } ;
struct TYPE_3__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_panel_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_unprepare (int /*<<< orphan*/ ) ; 
 struct rockchip_lvds* encoder_to_lvds (struct drm_encoder*) ; 
 int /*<<< orphan*/  rockchip_lvds_grf_config (struct drm_encoder*,struct drm_display_mode*) ; 
 int rockchip_lvds_poweron (struct rockchip_lvds*) ; 
 int /*<<< orphan*/  rockchip_lvds_set_vop_source (struct rockchip_lvds*,struct drm_encoder*) ; 

__attribute__((used)) static void rockchip_lvds_encoder_enable(struct drm_encoder *encoder)
{
	struct rockchip_lvds *lvds = encoder_to_lvds(encoder);
	struct drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	int ret;

	drm_panel_prepare(lvds->panel);
	ret = rockchip_lvds_poweron(lvds);
	if (ret < 0) {
		DRM_DEV_ERROR(lvds->dev, "failed to power on lvds: %d\n", ret);
		drm_panel_unprepare(lvds->panel);
	}
	rockchip_lvds_grf_config(encoder, mode);
	rockchip_lvds_set_vop_source(lvds, encoder);
	drm_panel_enable(lvds->panel);
}