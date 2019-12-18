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
struct drm_encoder {struct drm_crtc* crtc; } ;
struct drm_crtc_helper_funcs {int /*<<< orphan*/  (* dpms ) (struct drm_crtc*,int /*<<< orphan*/ ) ;} ;
struct drm_crtc {struct drm_crtc_helper_funcs* helper_private; } ;
struct drm_connector {int dpms; int /*<<< orphan*/  dev; struct drm_encoder* encoder; } ;

/* Variables and functions */
 int DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_drv_uses_atomic_modeset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_helper_choose_crtc_dpms (struct drm_crtc*) ; 
 int drm_helper_choose_encoder_dpms (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_helper_encoder_dpms (struct drm_encoder*,int) ; 
 int /*<<< orphan*/  stub1 (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct drm_crtc*,int /*<<< orphan*/ ) ; 

int drm_helper_connector_dpms(struct drm_connector *connector, int mode)
{
	struct drm_encoder *encoder = connector->encoder;
	struct drm_crtc *crtc = encoder ? encoder->crtc : NULL;
	int old_dpms, encoder_dpms = DRM_MODE_DPMS_OFF;

	WARN_ON(drm_drv_uses_atomic_modeset(connector->dev));

	if (mode == connector->dpms)
		return 0;

	old_dpms = connector->dpms;
	connector->dpms = mode;

	if (encoder)
		encoder_dpms = drm_helper_choose_encoder_dpms(encoder);

	/* from off to on, do crtc then encoder */
	if (mode < old_dpms) {
		if (crtc) {
			const struct drm_crtc_helper_funcs *crtc_funcs = crtc->helper_private;
			if (crtc_funcs->dpms)
				(*crtc_funcs->dpms) (crtc,
						     drm_helper_choose_crtc_dpms(crtc));
		}
		if (encoder)
			drm_helper_encoder_dpms(encoder, encoder_dpms);
	}

	/* from on to off, do encoder then crtc */
	if (mode > old_dpms) {
		if (encoder)
			drm_helper_encoder_dpms(encoder, encoder_dpms);
		if (crtc) {
			const struct drm_crtc_helper_funcs *crtc_funcs = crtc->helper_private;
			if (crtc_funcs->dpms)
				(*crtc_funcs->dpms) (crtc,
						     drm_helper_choose_crtc_dpms(crtc));
		}
	}

	return 0;
}