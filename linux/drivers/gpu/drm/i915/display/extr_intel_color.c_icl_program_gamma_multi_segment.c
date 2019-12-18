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
typedef  int u32 ;
struct TYPE_4__ {struct drm_property_blob* gamma_lut; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_property_blob {struct drm_color_lut* data; } ;
struct drm_i915_private {int dummy; } ;
struct drm_color_lut {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAL_PREC_AUTO_INCREMENT ; 
 int /*<<< orphan*/  PREC_PAL_DATA (int) ; 
 int /*<<< orphan*/  PREC_PAL_INDEX (int) ; 
 int /*<<< orphan*/  icl_load_gcmax (struct intel_crtc_state const*,struct drm_color_lut const*) ; 
 int /*<<< orphan*/  ilk_lut_12p4_ldw (struct drm_color_lut const*) ; 
 int /*<<< orphan*/  ilk_lut_12p4_udw (struct drm_color_lut const*) ; 
 int /*<<< orphan*/  ivb_load_lut_ext_max (struct intel_crtc*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
icl_program_gamma_multi_segment(const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	const struct drm_property_blob *blob = crtc_state->base.gamma_lut;
	const struct drm_color_lut *lut = blob->data;
	const struct drm_color_lut *entry;
	enum pipe pipe = crtc->pipe;
	u32 i;

	/*
	 *
	 * Program Fine segment (let's call it seg2)...
	 *
	 * Fine segment's step is 1/(128 * 256) ie 1/(128 * 256),  2/(128*256)
	 * ... 256/(128*256). So in order to program fine segment of LUT we
	 * need to pick every 8'th entry in LUT, and program 256 indexes.
	 *
	 * PAL_PREC_INDEX[0] and PAL_PREC_INDEX[1] map to seg2[1],
	 * with seg2[0] being unused by the hardware.
	 */
	I915_WRITE(PREC_PAL_INDEX(pipe), PAL_PREC_AUTO_INCREMENT);
	for (i = 1; i < 257; i++) {
		entry = &lut[i * 8];
		I915_WRITE(PREC_PAL_DATA(pipe), ilk_lut_12p4_ldw(entry));
		I915_WRITE(PREC_PAL_DATA(pipe), ilk_lut_12p4_udw(entry));
	}

	/*
	 * Program Coarse segment (let's call it seg3)...
	 *
	 * Coarse segment's starts from index 0 and it's step is 1/256 ie 0,
	 * 1/256, 2/256 ...256/256. As per the description of each entry in LUT
	 * above, we need to pick every (8 * 128)th entry in LUT, and
	 * program 256 of those.
	 *
	 * Spec is not very clear about if entries seg3[0] and seg3[1] are
	 * being used or not, but we still need to program these to advance
	 * the index.
	 */
	for (i = 0; i < 256; i++) {
		entry = &lut[i * 8 * 128];
		I915_WRITE(PREC_PAL_DATA(pipe), ilk_lut_12p4_ldw(entry));
		I915_WRITE(PREC_PAL_DATA(pipe), ilk_lut_12p4_udw(entry));
	}

	/* The last entry in the LUT is to be programmed in GCMAX */
	entry = &lut[256 * 8 * 128];
	icl_load_gcmax(crtc_state, entry);
	ivb_load_lut_ext_max(crtc);
}