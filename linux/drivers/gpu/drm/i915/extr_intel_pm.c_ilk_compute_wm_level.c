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
typedef  int u16 ;
struct intel_wm_level {int enable; int /*<<< orphan*/  cur_val; int /*<<< orphan*/  spr_val; int /*<<< orphan*/  pri_val; int /*<<< orphan*/  fbc_val; } ;
struct intel_plane_state {int dummy; } ;
struct intel_crtc_state {int dummy; } ;
struct intel_crtc {int dummy; } ;
struct TYPE_2__ {int* pri_latency; int* spr_latency; int* cur_latency; } ;
struct drm_i915_private {TYPE_1__ wm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ilk_compute_cur_wm (struct intel_crtc_state*,struct intel_plane_state const*,int) ; 
 int /*<<< orphan*/  ilk_compute_fbc_wm (struct intel_crtc_state*,struct intel_plane_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilk_compute_pri_wm (struct intel_crtc_state*,struct intel_plane_state const*,int,int) ; 
 int /*<<< orphan*/  ilk_compute_spr_wm (struct intel_crtc_state*,struct intel_plane_state const*,int) ; 

__attribute__((used)) static void ilk_compute_wm_level(const struct drm_i915_private *dev_priv,
				 const struct intel_crtc *intel_crtc,
				 int level,
				 struct intel_crtc_state *crtc_state,
				 const struct intel_plane_state *pristate,
				 const struct intel_plane_state *sprstate,
				 const struct intel_plane_state *curstate,
				 struct intel_wm_level *result)
{
	u16 pri_latency = dev_priv->wm.pri_latency[level];
	u16 spr_latency = dev_priv->wm.spr_latency[level];
	u16 cur_latency = dev_priv->wm.cur_latency[level];

	/* WM1+ latency values stored in 0.5us units */
	if (level > 0) {
		pri_latency *= 5;
		spr_latency *= 5;
		cur_latency *= 5;
	}

	if (pristate) {
		result->pri_val = ilk_compute_pri_wm(crtc_state, pristate,
						     pri_latency, level);
		result->fbc_val = ilk_compute_fbc_wm(crtc_state, pristate, result->pri_val);
	}

	if (sprstate)
		result->spr_val = ilk_compute_spr_wm(crtc_state, sprstate, spr_latency);

	if (curstate)
		result->cur_val = ilk_compute_cur_wm(crtc_state, curstate, cur_latency);

	result->enable = true;
}