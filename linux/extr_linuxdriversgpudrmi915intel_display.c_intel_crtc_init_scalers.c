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
struct intel_scaler {int /*<<< orphan*/  mode; scalar_t__ in_use; } ;
struct intel_crtc_scaler_state {int scaler_id; struct intel_scaler* scalers; } ;
struct intel_crtc_state {struct intel_crtc_scaler_state scaler_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int num_scalers; size_t pipe; TYPE_1__ base; } ;
struct TYPE_4__ {int* num_scalers; } ;
struct drm_i915_private {TYPE_2__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS_SCALER_MODE_DYN ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_crtc_init_scalers(struct intel_crtc *crtc,
				    struct intel_crtc_state *crtc_state)
{
	struct intel_crtc_scaler_state *scaler_state =
		&crtc_state->scaler_state;
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	int i;

	crtc->num_scalers = dev_priv->info.num_scalers[crtc->pipe];
	if (!crtc->num_scalers)
		return;

	for (i = 0; i < crtc->num_scalers; i++) {
		struct intel_scaler *scaler = &scaler_state->scalers[i];

		scaler->in_use = 0;
		scaler->mode = PS_SCALER_MODE_DYN;
	}

	scaler_state->scaler_id = -1;
}