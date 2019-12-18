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
 int /*<<< orphan*/  GEN12_PAT_INDEX (int) ; 
 int /*<<< orphan*/  GEN8_PPAT_UC ; 
 int /*<<< orphan*/  GEN8_PPAT_WB ; 
 int /*<<< orphan*/  GEN8_PPAT_WC ; 
 int /*<<< orphan*/  GEN8_PPAT_WT ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tgl_setup_private_ppat(struct drm_i915_private *dev_priv)
{
	/* TGL doesn't support LLC or AGE settings */
	I915_WRITE(GEN12_PAT_INDEX(0), GEN8_PPAT_WB);
	I915_WRITE(GEN12_PAT_INDEX(1), GEN8_PPAT_WC);
	I915_WRITE(GEN12_PAT_INDEX(2), GEN8_PPAT_WT);
	I915_WRITE(GEN12_PAT_INDEX(3), GEN8_PPAT_UC);
	I915_WRITE(GEN12_PAT_INDEX(4), GEN8_PPAT_WB);
	I915_WRITE(GEN12_PAT_INDEX(5), GEN8_PPAT_WB);
	I915_WRITE(GEN12_PAT_INDEX(6), GEN8_PPAT_WB);
	I915_WRITE(GEN12_PAT_INDEX(7), GEN8_PPAT_WB);
}