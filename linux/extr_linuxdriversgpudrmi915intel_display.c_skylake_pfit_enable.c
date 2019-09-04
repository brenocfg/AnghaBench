#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct intel_crtc_scaler_state {scalar_t__ scaler_id; TYPE_2__* scalers; } ;
struct TYPE_5__ {struct drm_device* dev; } ;
struct intel_crtc {int pipe; TYPE_4__* config; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_7__ {int pos; int size; scalar_t__ enabled; } ;
struct TYPE_8__ {TYPE_3__ pch_pfit; struct intel_crtc_scaler_state scaler_state; } ;
struct TYPE_6__ {int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 int PS_FILTER_MEDIUM ; 
 int PS_SCALER_EN ; 
 int PS_UV_RGB_PHASE (int /*<<< orphan*/ ) ; 
 int PS_Y_PHASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKL_PS_CTRL (int,int) ; 
 int /*<<< orphan*/  SKL_PS_HPHASE (int,int) ; 
 int /*<<< orphan*/  SKL_PS_VPHASE (int,int) ; 
 int /*<<< orphan*/  SKL_PS_WIN_POS (int,int) ; 
 int /*<<< orphan*/  SKL_PS_WIN_SZ (int,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  skl_scaler_calc_phase (int,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void skylake_pfit_enable(struct intel_crtc *crtc)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	int pipe = crtc->pipe;
	struct intel_crtc_scaler_state *scaler_state =
		&crtc->config->scaler_state;

	if (crtc->config->pch_pfit.enabled) {
		u16 uv_rgb_hphase, uv_rgb_vphase;
		int id;

		if (WARN_ON(crtc->config->scaler_state.scaler_id < 0))
			return;

		uv_rgb_hphase = skl_scaler_calc_phase(1, false);
		uv_rgb_vphase = skl_scaler_calc_phase(1, false);

		id = scaler_state->scaler_id;
		I915_WRITE(SKL_PS_CTRL(pipe, id), PS_SCALER_EN |
			PS_FILTER_MEDIUM | scaler_state->scalers[id].mode);
		I915_WRITE_FW(SKL_PS_VPHASE(pipe, id),
			      PS_Y_PHASE(0) | PS_UV_RGB_PHASE(uv_rgb_vphase));
		I915_WRITE_FW(SKL_PS_HPHASE(pipe, id),
			      PS_Y_PHASE(0) | PS_UV_RGB_PHASE(uv_rgb_hphase));
		I915_WRITE(SKL_PS_WIN_POS(pipe, id), crtc->config->pch_pfit.pos);
		I915_WRITE(SKL_PS_WIN_SZ(pipe, id), crtc->config->pch_pfit.size);
	}
}