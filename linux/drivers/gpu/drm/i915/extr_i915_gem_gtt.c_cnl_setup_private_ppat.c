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

/* Variables and functions */
 int /*<<< orphan*/  GEN10_PAT_INDEX (int) ; 
 int GEN8_PPAT_AGE (int) ; 
 int GEN8_PPAT_LLC ; 
 int GEN8_PPAT_LLCELLC ; 
 int GEN8_PPAT_UC ; 
 int GEN8_PPAT_WB ; 
 int GEN8_PPAT_WC ; 
 int GEN8_PPAT_WT ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cnl_setup_private_ppat(struct drm_i915_private *dev_priv)
{
	I915_WRITE(GEN10_PAT_INDEX(0), GEN8_PPAT_WB | GEN8_PPAT_LLC);
	I915_WRITE(GEN10_PAT_INDEX(1), GEN8_PPAT_WC | GEN8_PPAT_LLCELLC);
	I915_WRITE(GEN10_PAT_INDEX(2), GEN8_PPAT_WT | GEN8_PPAT_LLCELLC);
	I915_WRITE(GEN10_PAT_INDEX(3), GEN8_PPAT_UC);
	I915_WRITE(GEN10_PAT_INDEX(4), GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(0));
	I915_WRITE(GEN10_PAT_INDEX(5), GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(1));
	I915_WRITE(GEN10_PAT_INDEX(6), GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(2));
	I915_WRITE(GEN10_PAT_INDEX(7), GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(3));
}