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
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WM1_LP_ILK ; 
 int WM1_LP_SR_EN ; 
 int /*<<< orphan*/  WM2_LP_ILK ; 
 int /*<<< orphan*/  WM3_LP_ILK ; 

__attribute__((used)) static void ilk_init_lp_watermarks(struct drm_i915_private *dev_priv)
{
	I915_WRITE(WM3_LP_ILK, I915_READ(WM3_LP_ILK) & ~WM1_LP_SR_EN);
	I915_WRITE(WM2_LP_ILK, I915_READ(WM2_LP_ILK) & ~WM1_LP_SR_EN);
	I915_WRITE(WM1_LP_ILK, I915_READ(WM1_LP_ILK) & ~WM1_LP_SR_EN);

	/*
	 * Don't touch WM1S_LP_EN here.
	 * Doing so could cause underruns.
	 */
}