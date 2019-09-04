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
 int /*<<< orphan*/  CHICKEN_PIPESL_1 (int) ; 
 int /*<<< orphan*/  HSW_FBCQ_DIS ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 

__attribute__((used)) static void
skl_wa_528(struct drm_i915_private *dev_priv, int pipe, bool enable)
{
	if (IS_SKYLAKE(dev_priv) || IS_BROXTON(dev_priv))
		return;

	if (enable)
		I915_WRITE(CHICKEN_PIPESL_1(pipe), HSW_FBCQ_DIS);
	else
		I915_WRITE(CHICKEN_PIPESL_1(pipe), 0);
}