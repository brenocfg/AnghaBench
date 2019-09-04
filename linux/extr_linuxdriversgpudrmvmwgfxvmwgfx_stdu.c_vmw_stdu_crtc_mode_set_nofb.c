#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct drm_connector_state* state; } ;
struct TYPE_6__ {scalar_t__ is_implicit; TYPE_1__ connector; } ;
struct vmw_screen_target_display_unit {TYPE_3__ base; int /*<<< orphan*/  content_fb_type; scalar_t__ defined; } ;
struct vmw_private {int dummy; } ;
struct vmw_connector_state {int gui_x; int gui_y; } ;
struct drm_crtc {int x; int y; int /*<<< orphan*/  mode; TYPE_2__* state; int /*<<< orphan*/  dev; } ;
struct drm_connector_state {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  SAME_AS_DISPLAY ; 
 struct vmw_connector_state* vmw_connector_state_to_vcs (struct drm_connector_state*) ; 
 struct vmw_screen_target_display_unit* vmw_crtc_to_stdu (struct drm_crtc*) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 
 int vmw_stdu_bind_st (struct vmw_private*,struct vmw_screen_target_display_unit*,int /*<<< orphan*/ *) ; 
 int vmw_stdu_define_st (struct vmw_private*,struct vmw_screen_target_display_unit*,int /*<<< orphan*/ *,int,int) ; 
 int vmw_stdu_destroy_st (struct vmw_private*,struct vmw_screen_target_display_unit*) ; 
 int /*<<< orphan*/  vmw_stdu_update_st (struct vmw_private*,struct vmw_screen_target_display_unit*) ; 
 int /*<<< orphan*/  vmw_svga_enable (struct vmw_private*) ; 

__attribute__((used)) static void vmw_stdu_crtc_mode_set_nofb(struct drm_crtc *crtc)
{
	struct vmw_private *dev_priv;
	struct vmw_screen_target_display_unit *stdu;
	struct drm_connector_state *conn_state;
	struct vmw_connector_state *vmw_conn_state;
	int x, y, ret;

	stdu = vmw_crtc_to_stdu(crtc);
	dev_priv = vmw_priv(crtc->dev);
	conn_state = stdu->base.connector.state;
	vmw_conn_state = vmw_connector_state_to_vcs(conn_state);

	if (stdu->defined) {
		ret = vmw_stdu_bind_st(dev_priv, stdu, NULL);
		if (ret)
			DRM_ERROR("Failed to blank CRTC\n");

		(void) vmw_stdu_update_st(dev_priv, stdu);

		ret = vmw_stdu_destroy_st(dev_priv, stdu);
		if (ret)
			DRM_ERROR("Failed to destroy Screen Target\n");

		stdu->content_fb_type = SAME_AS_DISPLAY;
	}

	if (!crtc->state->enable)
		return;

	if (stdu->base.is_implicit) {
		x = crtc->x;
		y = crtc->y;
	} else {
		x = vmw_conn_state->gui_x;
		y = vmw_conn_state->gui_y;
	}

	vmw_svga_enable(dev_priv);
	ret = vmw_stdu_define_st(dev_priv, stdu, &crtc->mode, x, y);

	if (ret)
		DRM_ERROR("Failed to define Screen Target of size %dx%d\n",
			  crtc->x, crtc->y);
}