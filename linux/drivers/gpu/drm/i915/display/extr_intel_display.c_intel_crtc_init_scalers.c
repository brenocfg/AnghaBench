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
struct intel_scaler {scalar_t__ mode; scalar_t__ in_use; } ;
struct intel_crtc_scaler_state {int scaler_id; struct intel_scaler* scalers; } ;
struct intel_crtc_state {struct intel_crtc_scaler_state scaler_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int num_scalers; size_t pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {int* num_scalers; } ;

/* Variables and functions */
 TYPE_2__* RUNTIME_INFO (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_crtc_init_scalers(struct intel_crtc *crtc,
				    struct intel_crtc_state *crtc_state)
{
	struct intel_crtc_scaler_state *scaler_state =
		&crtc_state->scaler_state;
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	int i;

	crtc->num_scalers = RUNTIME_INFO(dev_priv)->num_scalers[crtc->pipe];
	if (!crtc->num_scalers)
		return;

	for (i = 0; i < crtc->num_scalers; i++) {
		struct intel_scaler *scaler = &scaler_state->scalers[i];

		scaler->in_use = 0;
		scaler->mode = 0;
	}

	scaler_state->scaler_id = -1;
}