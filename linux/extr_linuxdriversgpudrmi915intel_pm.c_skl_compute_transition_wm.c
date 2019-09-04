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
typedef  scalar_t__ uint16_t ;
struct skl_wm_params {int /*<<< orphan*/  y_tile_minimum; scalar_t__ y_tiled; } ;
struct skl_wm_level {scalar_t__ plane_res_b; int plane_en; } ;
struct TYPE_4__ {int /*<<< orphan*/  active; TYPE_1__* crtc; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  ipc_enabled; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_REVID_A0 ; 
 int INTEL_GEN (struct drm_i915_private const*) ; 
 scalar_t__ IS_CNL_REVID (struct drm_i915_private const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ mul_round_up_u32_fixed16 (int,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void skl_compute_transition_wm(struct intel_crtc_state *cstate,
				      struct skl_wm_params *wp,
				      struct skl_wm_level *wm_l0,
				      uint16_t ddb_allocation,
				      struct skl_wm_level *trans_wm /* out */)
{
	struct drm_device *dev = cstate->base.crtc->dev;
	const struct drm_i915_private *dev_priv = to_i915(dev);
	uint16_t trans_min, trans_y_tile_min;
	const uint16_t trans_amount = 10; /* This is configurable amount */
	uint16_t trans_offset_b, res_blocks;

	if (!cstate->base.active)
		goto exit;

	/* Transition WM are not recommended by HW team for GEN9 */
	if (INTEL_GEN(dev_priv) <= 9)
		goto exit;

	/* Transition WM don't make any sense if ipc is disabled */
	if (!dev_priv->ipc_enabled)
		goto exit;

	trans_min = 0;
	if (INTEL_GEN(dev_priv) >= 10)
		trans_min = 4;

	trans_offset_b = trans_min + trans_amount;

	if (wp->y_tiled) {
		trans_y_tile_min = (uint16_t) mul_round_up_u32_fixed16(2,
							wp->y_tile_minimum);
		res_blocks = max(wm_l0->plane_res_b, trans_y_tile_min) +
				trans_offset_b;
	} else {
		res_blocks = wm_l0->plane_res_b + trans_offset_b;

		/* WA BUG:1938466 add one block for non y-tile planes */
		if (IS_CNL_REVID(dev_priv, CNL_REVID_A0, CNL_REVID_A0))
			res_blocks += 1;

	}

	res_blocks += 1;

	if (res_blocks < ddb_allocation) {
		trans_wm->plane_res_b = res_blocks;
		trans_wm->plane_en = true;
		return;
	}

exit:
	trans_wm->plane_en = false;
}