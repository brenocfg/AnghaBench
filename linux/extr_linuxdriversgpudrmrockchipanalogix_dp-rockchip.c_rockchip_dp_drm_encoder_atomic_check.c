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
struct rockchip_crtc_state {int /*<<< orphan*/  output_bpc; int /*<<< orphan*/  output_type; int /*<<< orphan*/  output_mode; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_info {int /*<<< orphan*/  bpc; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_connector_state {TYPE_1__* connector; } ;
struct TYPE_2__ {struct drm_display_info display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_eDP ; 
 int /*<<< orphan*/  ROCKCHIP_OUT_MODE_AAAA ; 
 struct rockchip_crtc_state* to_rockchip_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static int
rockchip_dp_drm_encoder_atomic_check(struct drm_encoder *encoder,
				      struct drm_crtc_state *crtc_state,
				      struct drm_connector_state *conn_state)
{
	struct rockchip_crtc_state *s = to_rockchip_crtc_state(crtc_state);
	struct drm_display_info *di = &conn_state->connector->display_info;

	/*
	 * The hardware IC designed that VOP must output the RGB10 video
	 * format to eDP controller, and if eDP panel only support RGB8,
	 * then eDP controller should cut down the video data, not via VOP
	 * controller, that's why we need to hardcode the VOP output mode
	 * to RGA10 here.
	 */

	s->output_mode = ROCKCHIP_OUT_MODE_AAAA;
	s->output_type = DRM_MODE_CONNECTOR_eDP;
	s->output_bpc = di->bpc;

	return 0;
}