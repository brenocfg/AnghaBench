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
struct TYPE_4__ {int ctrl; } ;
struct nv50_outp_atom {int flush_disable; TYPE_2__ clr; TYPE_1__* encoder; } ;
struct nv50_atom {int flush_disable; int lock_core; int /*<<< orphan*/  state; } ;
struct drm_encoder {int dummy; } ;
struct drm_crtc_state {scalar_t__ active; } ;
struct drm_crtc {int dummy; } ;
struct drm_connector_state {struct drm_crtc* crtc; struct drm_encoder* best_encoder; } ;
struct TYPE_3__ {scalar_t__ encoder_type; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_ENCODER_DPMST ; 
 scalar_t__ IS_ERR (struct nv50_outp_atom*) ; 
 int PTR_ERR (struct nv50_outp_atom*) ; 
 scalar_t__ drm_atomic_crtc_needs_modeset (struct drm_crtc_state*) ; 
 struct drm_crtc_state* drm_atomic_get_new_crtc_state (int /*<<< orphan*/ *,struct drm_crtc*) ; 
 struct drm_crtc_state* drm_atomic_get_old_crtc_state (int /*<<< orphan*/ *,struct drm_crtc*) ; 
 struct nv50_outp_atom* nv50_disp_outp_atomic_add (struct nv50_atom*,struct drm_encoder*) ; 

__attribute__((used)) static int
nv50_disp_outp_atomic_check_clr(struct nv50_atom *atom,
				struct drm_connector_state *old_connector_state)
{
	struct drm_encoder *encoder = old_connector_state->best_encoder;
	struct drm_crtc_state *old_crtc_state, *new_crtc_state;
	struct drm_crtc *crtc;
	struct nv50_outp_atom *outp;

	if (!(crtc = old_connector_state->crtc))
		return 0;

	old_crtc_state = drm_atomic_get_old_crtc_state(&atom->state, crtc);
	new_crtc_state = drm_atomic_get_new_crtc_state(&atom->state, crtc);
	if (old_crtc_state->active && drm_atomic_crtc_needs_modeset(new_crtc_state)) {
		outp = nv50_disp_outp_atomic_add(atom, encoder);
		if (IS_ERR(outp))
			return PTR_ERR(outp);

		if (outp->encoder->encoder_type == DRM_MODE_ENCODER_DPMST) {
			outp->flush_disable = true;
			atom->flush_disable = true;
		}
		outp->clr.ctrl = true;
		atom->lock_core = true;
	}

	return 0;
}