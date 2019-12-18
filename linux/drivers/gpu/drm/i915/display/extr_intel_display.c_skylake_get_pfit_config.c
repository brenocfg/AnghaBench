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
typedef  int u32 ;
struct TYPE_5__ {int enabled; void* size; void* pos; } ;
struct intel_crtc_scaler_state {int scaler_id; int scaler_users; TYPE_3__* scalers; } ;
struct intel_crtc_state {TYPE_2__ pch_pfit; struct intel_crtc_scaler_state scaler_state; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct intel_crtc {int num_scalers; int /*<<< orphan*/  pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_6__ {int in_use; } ;

/* Variables and functions */
 void* I915_READ (int /*<<< orphan*/ ) ; 
 int PS_PLANE_SEL_MASK ; 
 int PS_SCALER_EN ; 
 int SKL_CRTC_INDEX ; 
 int /*<<< orphan*/  SKL_PS_CTRL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SKL_PS_WIN_POS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SKL_PS_WIN_SZ (int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void skylake_get_pfit_config(struct intel_crtc *crtc,
				    struct intel_crtc_state *pipe_config)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_crtc_scaler_state *scaler_state = &pipe_config->scaler_state;
	u32 ps_ctrl = 0;
	int id = -1;
	int i;

	/* find scaler attached to this pipe */
	for (i = 0; i < crtc->num_scalers; i++) {
		ps_ctrl = I915_READ(SKL_PS_CTRL(crtc->pipe, i));
		if (ps_ctrl & PS_SCALER_EN && !(ps_ctrl & PS_PLANE_SEL_MASK)) {
			id = i;
			pipe_config->pch_pfit.enabled = true;
			pipe_config->pch_pfit.pos = I915_READ(SKL_PS_WIN_POS(crtc->pipe, i));
			pipe_config->pch_pfit.size = I915_READ(SKL_PS_WIN_SZ(crtc->pipe, i));
			scaler_state->scalers[i].in_use = true;
			break;
		}
	}

	scaler_state->scaler_id = id;
	if (id >= 0) {
		scaler_state->scaler_users |= (1 << SKL_CRTC_INDEX);
	} else {
		scaler_state->scaler_users &= ~(1 << SKL_CRTC_INDEX);
	}
}