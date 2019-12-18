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
typedef  int u32 ;
struct vc4_plane_state {scalar_t__* y_scaling; int /*<<< orphan*/  is_yuv; scalar_t__ crtc_w; int /*<<< orphan*/ * src_w; } ;
struct drm_plane_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ VC4_SCALING_NONE ; 
 scalar_t__ VC4_SCALING_TPZ ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int roundup (int,int) ; 
 struct vc4_plane_state* to_vc4_plane_state (struct drm_plane_state*) ; 

__attribute__((used)) static u32 vc4_lbm_size(struct drm_plane_state *state)
{
	struct vc4_plane_state *vc4_state = to_vc4_plane_state(state);
	/* This is the worst case number.  One of the two sizes will
	 * be used depending on the scaling configuration.
	 */
	u32 pix_per_line = max(vc4_state->src_w[0], (u32)vc4_state->crtc_w);
	u32 lbm;

	/* LBM is not needed when there's no vertical scaling. */
	if (vc4_state->y_scaling[0] == VC4_SCALING_NONE &&
	    vc4_state->y_scaling[1] == VC4_SCALING_NONE)
		return 0;

	if (!vc4_state->is_yuv) {
		if (vc4_state->y_scaling[0] == VC4_SCALING_TPZ)
			lbm = pix_per_line * 8;
		else {
			/* In special cases, this multiplier might be 12. */
			lbm = pix_per_line * 16;
		}
	} else {
		/* There are cases for this going down to a multiplier
		 * of 2, but according to the firmware source, the
		 * table in the docs is somewhat wrong.
		 */
		lbm = pix_per_line * 16;
	}

	lbm = roundup(lbm, 32);

	return lbm;
}