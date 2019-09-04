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
struct drm_i915_private {int dummy; } ;
struct color_conversion {int ry; int gy; int by; int ay; int ru; int gu; int bu; int au; int rv; int gv; int bv; int av; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TV_CSC_U ; 
 int /*<<< orphan*/  TV_CSC_U2 ; 
 int /*<<< orphan*/  TV_CSC_V ; 
 int /*<<< orphan*/  TV_CSC_V2 ; 
 int /*<<< orphan*/  TV_CSC_Y ; 
 int /*<<< orphan*/  TV_CSC_Y2 ; 

__attribute__((used)) static void set_color_conversion(struct drm_i915_private *dev_priv,
				 const struct color_conversion *color_conversion)
{
	if (!color_conversion)
		return;

	I915_WRITE(TV_CSC_Y, (color_conversion->ry << 16) |
		   color_conversion->gy);
	I915_WRITE(TV_CSC_Y2, (color_conversion->by << 16) |
		   color_conversion->ay);
	I915_WRITE(TV_CSC_U, (color_conversion->ru << 16) |
		   color_conversion->gu);
	I915_WRITE(TV_CSC_U2, (color_conversion->bu << 16) |
		   color_conversion->au);
	I915_WRITE(TV_CSC_V, (color_conversion->rv << 16) |
		   color_conversion->gv);
	I915_WRITE(TV_CSC_V2, (color_conversion->bv << 16) |
		   color_conversion->av);
}