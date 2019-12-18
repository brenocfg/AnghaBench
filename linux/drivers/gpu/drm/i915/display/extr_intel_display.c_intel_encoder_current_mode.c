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
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int /*<<< orphan*/  (* get_config ) (struct intel_encoder*,struct intel_crtc_state*) ;int /*<<< orphan*/  (* get_hw_state ) (struct intel_encoder*,int*) ;TYPE_3__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/ * crtc; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct intel_crtc {int /*<<< orphan*/  base; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_pipe_config ) (struct intel_crtc*,struct intel_crtc_state*) ;} ;
struct drm_i915_private {TYPE_2__ display; } ;
struct drm_display_mode {TYPE_1__ base; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct intel_crtc* intel_get_crtc_for_pipe (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_mode_from_pipe_config (struct intel_crtc_state*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  kfree (struct intel_crtc_state*) ; 
 struct intel_crtc_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct intel_encoder*,int*) ; 
 int /*<<< orphan*/  stub2 (struct intel_crtc*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  stub3 (struct intel_encoder*,struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

struct drm_display_mode *
intel_encoder_current_mode(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_crtc_state *crtc_state;
	struct drm_display_mode *mode;
	struct intel_crtc *crtc;
	enum pipe pipe;

	if (!encoder->get_hw_state(encoder, &pipe))
		return NULL;

	crtc = intel_get_crtc_for_pipe(dev_priv, pipe);

	mode = kzalloc(sizeof(*mode), GFP_KERNEL);
	if (!mode)
		return NULL;

	crtc_state = kzalloc(sizeof(*crtc_state), GFP_KERNEL);
	if (!crtc_state) {
		kfree(mode);
		return NULL;
	}

	crtc_state->base.crtc = &crtc->base;

	if (!dev_priv->display.get_pipe_config(crtc, crtc_state)) {
		kfree(crtc_state);
		kfree(mode);
		return NULL;
	}

	encoder->get_config(encoder, crtc_state);

	intel_mode_from_pipe_config(mode, crtc_state);

	kfree(crtc_state);

	return mode;
}