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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_property_blob {struct drm_color_lut* data; } ;
struct drm_i915_private {int dummy; } ;
struct drm_color_lut {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PALETTE (int,int) ; 
 int /*<<< orphan*/  PIPEGCMAX (int,int) ; 
 int drm_color_lut_size (struct drm_property_blob const*) ; 
 int /*<<< orphan*/  i965_lut_10p6_ldw (struct drm_color_lut const*) ; 
 int /*<<< orphan*/  i965_lut_10p6_udw (struct drm_color_lut const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i965_load_lut_10p6(struct intel_crtc *crtc,
			       const struct drm_property_blob *blob)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	const struct drm_color_lut *lut = blob->data;
	int i, lut_size = drm_color_lut_size(blob);
	enum pipe pipe = crtc->pipe;

	for (i = 0; i < lut_size - 1; i++) {
		I915_WRITE(PALETTE(pipe, 2 * i + 0),
			   i965_lut_10p6_ldw(&lut[i]));
		I915_WRITE(PALETTE(pipe, 2 * i + 1),
			   i965_lut_10p6_udw(&lut[i]));
	}

	I915_WRITE(PIPEGCMAX(pipe, 0), lut[i].red);
	I915_WRITE(PIPEGCMAX(pipe, 1), lut[i].green);
	I915_WRITE(PIPEGCMAX(pipe, 2), lut[i].blue);
}