#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct drm_i915_private {int dummy; } ;
struct drm_crtc_state {TYPE_2__* degamma_lut; TYPE_4__* crtc; } ;
struct drm_color_lut {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_6__ {size_t degamma_lut_size; } ;
struct TYPE_10__ {TYPE_1__ color; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int pipe; } ;
struct TYPE_7__ {struct drm_color_lut* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,size_t) ; 
 TYPE_5__* INTEL_INFO (struct drm_i915_private*) ; 
 size_t PAL_PREC_AUTO_INCREMENT ; 
 size_t PAL_PREC_SPLIT_MODE ; 
 int /*<<< orphan*/  PREC_PAL_DATA (int) ; 
 int /*<<< orphan*/  PREC_PAL_INDEX (int) ; 
 int drm_color_lut_extract (int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 TYPE_3__* to_intel_crtc (TYPE_4__*) ; 

__attribute__((used)) static void bdw_load_degamma_lut(struct drm_crtc_state *state)
{
	struct drm_i915_private *dev_priv = to_i915(state->crtc->dev);
	enum pipe pipe = to_intel_crtc(state->crtc)->pipe;
	uint32_t i, lut_size = INTEL_INFO(dev_priv)->color.degamma_lut_size;

	I915_WRITE(PREC_PAL_INDEX(pipe),
		   PAL_PREC_SPLIT_MODE | PAL_PREC_AUTO_INCREMENT);

	if (state->degamma_lut) {
		struct drm_color_lut *lut = state->degamma_lut->data;

		for (i = 0; i < lut_size; i++) {
			uint32_t word =
			drm_color_lut_extract(lut[i].red, 10) << 20 |
			drm_color_lut_extract(lut[i].green, 10) << 10 |
			drm_color_lut_extract(lut[i].blue, 10);

			I915_WRITE(PREC_PAL_DATA(pipe), word);
		}
	} else {
		for (i = 0; i < lut_size; i++) {
			uint32_t v = (i * ((1 << 10) - 1)) / (lut_size - 1);

			I915_WRITE(PREC_PAL_DATA(pipe),
				   (v << 20) | (v << 10) | v);
		}
	}
}