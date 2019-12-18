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
struct nouveau_drm {int dummy; } ;
struct TYPE_2__ {int full; scalar_t__ mode; } ;
struct nouveau_conn_atom {TYPE_1__ scaler; } ;
struct drm_encoder {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct drm_display_mode {int type; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct drm_crtc_state {int mode_changed; struct drm_display_mode mode; struct drm_display_mode adjusted_mode; } ;
struct drm_connector_state {struct drm_connector* connector; } ;
struct drm_connector {int connector_type; } ;

/* Variables and functions */
#define  DRM_MODE_CONNECTOR_LVDS 129 
#define  DRM_MODE_CONNECTOR_eDP 128 
 scalar_t__ DRM_MODE_SCALE_NONE ; 
 int DRM_MODE_TYPE_DRIVER ; 
 int /*<<< orphan*/  NV_ATOMIC (struct nouveau_drm*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_copy (struct drm_display_mode*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_equal (struct drm_display_mode*,struct drm_display_mode*) ; 
 struct nouveau_conn_atom* nouveau_conn_atom (struct drm_connector_state*) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv50_outp_atomic_check_view(struct drm_encoder *encoder,
			    struct drm_crtc_state *crtc_state,
			    struct drm_connector_state *conn_state,
			    struct drm_display_mode *native_mode)
{
	struct drm_display_mode *adjusted_mode = &crtc_state->adjusted_mode;
	struct drm_display_mode *mode = &crtc_state->mode;
	struct drm_connector *connector = conn_state->connector;
	struct nouveau_conn_atom *asyc = nouveau_conn_atom(conn_state);
	struct nouveau_drm *drm = nouveau_drm(encoder->dev);

	NV_ATOMIC(drm, "%s atomic_check\n", encoder->name);
	asyc->scaler.full = false;
	if (!native_mode)
		return 0;

	if (asyc->scaler.mode == DRM_MODE_SCALE_NONE) {
		switch (connector->connector_type) {
		case DRM_MODE_CONNECTOR_LVDS:
		case DRM_MODE_CONNECTOR_eDP:
			/* Don't force scaler for EDID modes with
			 * same size as the native one (e.g. different
			 * refresh rate)
			 */
			if (adjusted_mode->hdisplay == native_mode->hdisplay &&
			    adjusted_mode->vdisplay == native_mode->vdisplay &&
			    adjusted_mode->type & DRM_MODE_TYPE_DRIVER)
				break;
			mode = native_mode;
			asyc->scaler.full = true;
			break;
		default:
			break;
		}
	} else {
		mode = native_mode;
	}

	if (!drm_mode_equal(adjusted_mode, mode)) {
		drm_mode_copy(adjusted_mode, mode);
		crtc_state->mode_changed = true;
	}

	return 0;
}