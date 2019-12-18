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
typedef  int u16 ;
struct skl_wm_params {int /*<<< orphan*/  y_tile_minimum; scalar_t__ y_tiled; } ;
struct TYPE_8__ {int plane_res_b; int plane_en; } ;
struct skl_plane_wm {TYPE_4__ trans_wm; TYPE_3__* wm; } ;
struct TYPE_6__ {TYPE_1__* crtc; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  ipc_enabled; } ;
struct drm_device {int dummy; } ;
struct TYPE_7__ {int plane_res_b; } ;
struct TYPE_5__ {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_REVID_A0 ; 
 int INTEL_GEN (struct drm_i915_private const*) ; 
 scalar_t__ IS_CNL_REVID (struct drm_i915_private const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 scalar_t__ mul_round_up_u32_fixed16 (int,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void skl_compute_transition_wm(const struct intel_crtc_state *crtc_state,
				      const struct skl_wm_params *wp,
				      struct skl_plane_wm *wm)
{
	struct drm_device *dev = crtc_state->base.crtc->dev;
	const struct drm_i915_private *dev_priv = to_i915(dev);
	u16 trans_min, trans_y_tile_min;
	const u16 trans_amount = 10; /* This is configurable amount */
	u16 wm0_sel_res_b, trans_offset_b, res_blocks;

	/* Transition WM are not recommended by HW team for GEN9 */
	if (INTEL_GEN(dev_priv) <= 9)
		return;

	/* Transition WM don't make any sense if ipc is disabled */
	if (!dev_priv->ipc_enabled)
		return;

	trans_min = 14;
	if (INTEL_GEN(dev_priv) >= 11)
		trans_min = 4;

	trans_offset_b = trans_min + trans_amount;

	/*
	 * The spec asks for Selected Result Blocks for wm0 (the real value),
	 * not Result Blocks (the integer value). Pay attention to the capital
	 * letters. The value wm_l0->plane_res_b is actually Result Blocks, but
	 * since Result Blocks is the ceiling of Selected Result Blocks plus 1,
	 * and since we later will have to get the ceiling of the sum in the
	 * transition watermarks calculation, we can just pretend Selected
	 * Result Blocks is Result Blocks minus 1 and it should work for the
	 * current platforms.
	 */
	wm0_sel_res_b = wm->wm[0].plane_res_b - 1;

	if (wp->y_tiled) {
		trans_y_tile_min =
			(u16)mul_round_up_u32_fixed16(2, wp->y_tile_minimum);
		res_blocks = max(wm0_sel_res_b, trans_y_tile_min) +
				trans_offset_b;
	} else {
		res_blocks = wm0_sel_res_b + trans_offset_b;

		/* WA BUG:1938466 add one block for non y-tile planes */
		if (IS_CNL_REVID(dev_priv, CNL_REVID_A0, CNL_REVID_A0))
			res_blocks += 1;

	}

	/*
	 * Just assume we can enable the transition watermark.  After
	 * computing the DDB we'll come back and disable it if that
	 * assumption turns out to be false.
	 */
	wm->trans_wm.plane_res_b = res_blocks + 1;
	wm->trans_wm.plane_en = true;
}