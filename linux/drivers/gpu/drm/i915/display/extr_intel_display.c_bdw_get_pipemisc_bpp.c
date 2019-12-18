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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  PIPEMISC (int /*<<< orphan*/ ) ; 
#define  PIPEMISC_DITHER_10_BPC 131 
#define  PIPEMISC_DITHER_12_BPC 130 
#define  PIPEMISC_DITHER_6_BPC 129 
#define  PIPEMISC_DITHER_8_BPC 128 
 int PIPEMISC_DITHER_BPC_MASK ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

int bdw_get_pipemisc_bpp(struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	u32 tmp;

	tmp = I915_READ(PIPEMISC(crtc->pipe));

	switch (tmp & PIPEMISC_DITHER_BPC_MASK) {
	case PIPEMISC_DITHER_6_BPC:
		return 18;
	case PIPEMISC_DITHER_8_BPC:
		return 24;
	case PIPEMISC_DITHER_10_BPC:
		return 30;
	case PIPEMISC_DITHER_12_BPC:
		return 36;
	default:
		MISSING_CASE(tmp);
		return 0;
	}
}