#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rockchip_dp_device {int /*<<< orphan*/  grfclk; TYPE_2__* dev; TYPE_1__* data; int /*<<< orphan*/  grf; } ;
struct drm_encoder {int dummy; } ;
struct drm_crtc_state {scalar_t__ self_refresh_active; } ;
struct drm_crtc {int dummy; } ;
struct drm_atomic_state {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  lcdsel_grf_reg; int /*<<< orphan*/  lcdsel_big; int /*<<< orphan*/  lcdsel_lit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct drm_crtc_state* drm_atomic_get_old_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 int drm_of_encoder_active_endpoint_id (int /*<<< orphan*/ ,struct drm_encoder*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_crtc* rockchip_dp_drm_get_new_crtc (struct drm_encoder*,struct drm_atomic_state*) ; 
 struct rockchip_dp_device* to_dp (struct drm_encoder*) ; 

__attribute__((used)) static void rockchip_dp_drm_encoder_enable(struct drm_encoder *encoder,
					   struct drm_atomic_state *state)
{
	struct rockchip_dp_device *dp = to_dp(encoder);
	struct drm_crtc *crtc;
	struct drm_crtc_state *old_crtc_state;
	int ret;
	u32 val;

	crtc = rockchip_dp_drm_get_new_crtc(encoder, state);
	if (!crtc)
		return;

	old_crtc_state = drm_atomic_get_old_crtc_state(state, crtc);
	/* Coming back from self refresh, nothing to do */
	if (old_crtc_state && old_crtc_state->self_refresh_active)
		return;

	ret = drm_of_encoder_active_endpoint_id(dp->dev->of_node, encoder);
	if (ret < 0)
		return;

	if (ret)
		val = dp->data->lcdsel_lit;
	else
		val = dp->data->lcdsel_big;

	DRM_DEV_DEBUG(dp->dev, "vop %s output to dp\n", (ret) ? "LIT" : "BIG");

	ret = clk_prepare_enable(dp->grfclk);
	if (ret < 0) {
		DRM_DEV_ERROR(dp->dev, "failed to enable grfclk %d\n", ret);
		return;
	}

	ret = regmap_write(dp->grf, dp->data->lcdsel_grf_reg, val);
	if (ret != 0)
		DRM_DEV_ERROR(dp->dev, "Could not write to GRF: %d\n", ret);

	clk_disable_unprepare(dp->grfclk);
}