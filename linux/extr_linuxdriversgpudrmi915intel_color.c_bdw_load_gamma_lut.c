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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
struct drm_crtc_state {TYPE_2__* gamma_lut; TYPE_4__* crtc; } ;
struct drm_color_lut {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_6__ {size_t gamma_lut_size; } ;
struct TYPE_10__ {TYPE_1__ color; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int pipe; } ;
struct TYPE_7__ {struct drm_color_lut* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 TYPE_5__* INTEL_INFO (struct drm_i915_private*) ; 
 int PAL_PREC_AUTO_INCREMENT ; 
 int PAL_PREC_INDEX_VALUE_MASK ; 
 int PAL_PREC_SPLIT_MODE ; 
 int /*<<< orphan*/  PREC_PAL_DATA (int) ; 
 int /*<<< orphan*/  PREC_PAL_GC_MAX (int,int) ; 
 int /*<<< orphan*/  PREC_PAL_INDEX (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int drm_color_lut_extract (int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 TYPE_3__* to_intel_crtc (TYPE_4__*) ; 

__attribute__((used)) static void bdw_load_gamma_lut(struct drm_crtc_state *state, u32 offset)
{
	struct drm_i915_private *dev_priv = to_i915(state->crtc->dev);
	enum pipe pipe = to_intel_crtc(state->crtc)->pipe;
	uint32_t i, lut_size = INTEL_INFO(dev_priv)->color.gamma_lut_size;

	WARN_ON(offset & ~PAL_PREC_INDEX_VALUE_MASK);

	I915_WRITE(PREC_PAL_INDEX(pipe),
		   (offset ? PAL_PREC_SPLIT_MODE : 0) |
		   PAL_PREC_AUTO_INCREMENT |
		   offset);

	if (state->gamma_lut) {
		struct drm_color_lut *lut = state->gamma_lut->data;

		for (i = 0; i < lut_size; i++) {
			uint32_t word =
			(drm_color_lut_extract(lut[i].red, 10) << 20) |
			(drm_color_lut_extract(lut[i].green, 10) << 10) |
			drm_color_lut_extract(lut[i].blue, 10);

			I915_WRITE(PREC_PAL_DATA(pipe), word);
		}

		/* Program the max register to clamp values > 1.0. */
		i = lut_size - 1;
		I915_WRITE(PREC_PAL_GC_MAX(pipe, 0),
			   drm_color_lut_extract(lut[i].red, 16));
		I915_WRITE(PREC_PAL_GC_MAX(pipe, 1),
			   drm_color_lut_extract(lut[i].green, 16));
		I915_WRITE(PREC_PAL_GC_MAX(pipe, 2),
			   drm_color_lut_extract(lut[i].blue, 16));
	} else {
		for (i = 0; i < lut_size; i++) {
			uint32_t v = (i * ((1 << 10) - 1)) / (lut_size - 1);

			I915_WRITE(PREC_PAL_DATA(pipe),
				   (v << 20) | (v << 10) | v);
		}

		I915_WRITE(PREC_PAL_GC_MAX(pipe, 0), (1 << 16) - 1);
		I915_WRITE(PREC_PAL_GC_MAX(pipe, 1), (1 << 16) - 1);
		I915_WRITE(PREC_PAL_GC_MAX(pipe, 2), (1 << 16) - 1);
	}
}