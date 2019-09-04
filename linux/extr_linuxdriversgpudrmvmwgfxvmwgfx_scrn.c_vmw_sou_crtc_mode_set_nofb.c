#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct drm_connector_state* state; } ;
struct TYPE_7__ {TYPE_2__ connector; scalar_t__ is_implicit; } ;
struct vmw_screen_object_unit {TYPE_3__ base; scalar_t__ buffer_size; int /*<<< orphan*/ * buffer; scalar_t__ defined; } ;
struct vmw_private {int dummy; } ;
struct vmw_plane_state {scalar_t__ bo_size; int /*<<< orphan*/ * bo; } ;
struct vmw_framebuffer {int dummy; } ;
struct vmw_connector_state {int gui_x; int gui_y; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {int x; int y; int /*<<< orphan*/  mode; TYPE_1__* primary; int /*<<< orphan*/  dev; } ;
struct drm_connector_state {int dummy; } ;
struct TYPE_5__ {struct drm_plane_state* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 struct vmw_connector_state* vmw_connector_state_to_vcs (struct drm_connector_state*) ; 
 struct vmw_screen_object_unit* vmw_crtc_to_sou (struct drm_crtc*) ; 
 struct vmw_framebuffer* vmw_framebuffer_to_vfb (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  vmw_kms_add_active (struct vmw_private*,TYPE_3__*,struct vmw_framebuffer*) ; 
 int /*<<< orphan*/  vmw_kms_del_active (struct vmw_private*,TYPE_3__*) ; 
 struct vmw_plane_state* vmw_plane_state_to_vps (struct drm_plane_state*) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 
 int vmw_sou_fifo_create (struct vmw_private*,struct vmw_screen_object_unit*,int,int,int /*<<< orphan*/ *) ; 
 int vmw_sou_fifo_destroy (struct vmw_private*,struct vmw_screen_object_unit*) ; 

__attribute__((used)) static void vmw_sou_crtc_mode_set_nofb(struct drm_crtc *crtc)
{
	struct vmw_private *dev_priv;
	struct vmw_screen_object_unit *sou;
	struct vmw_framebuffer *vfb;
	struct drm_framebuffer *fb;
	struct drm_plane_state *ps;
	struct vmw_plane_state *vps;
	int ret;

	sou = vmw_crtc_to_sou(crtc);
	dev_priv = vmw_priv(crtc->dev);
	ps = crtc->primary->state;
	fb = ps->fb;
	vps = vmw_plane_state_to_vps(ps);

	vfb = (fb) ? vmw_framebuffer_to_vfb(fb) : NULL;

	if (sou->defined) {
		ret = vmw_sou_fifo_destroy(dev_priv, sou);
		if (ret) {
			DRM_ERROR("Failed to destroy Screen Object\n");
			return;
		}
	}

	if (vfb) {
		struct drm_connector_state *conn_state;
		struct vmw_connector_state *vmw_conn_state;
		int x, y;

		sou->buffer = vps->bo;
		sou->buffer_size = vps->bo_size;

		if (sou->base.is_implicit) {
			x = crtc->x;
			y = crtc->y;
		} else {
			conn_state = sou->base.connector.state;
			vmw_conn_state = vmw_connector_state_to_vcs(conn_state);

			x = vmw_conn_state->gui_x;
			y = vmw_conn_state->gui_y;
		}

		ret = vmw_sou_fifo_create(dev_priv, sou, x, y, &crtc->mode);
		if (ret)
			DRM_ERROR("Failed to define Screen Object %dx%d\n",
				  crtc->x, crtc->y);

		vmw_kms_add_active(dev_priv, &sou->base, vfb);
	} else {
		sou->buffer = NULL;
		sou->buffer_size = 0;

		vmw_kms_del_active(dev_priv, &sou->base);
	}
}