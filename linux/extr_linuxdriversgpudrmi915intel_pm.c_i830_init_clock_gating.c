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
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MEM_DISPLAY_A_TRICKLE_FEED_DISABLE ; 
 int /*<<< orphan*/  MEM_DISPLAY_B_TRICKLE_FEED_DISABLE ; 
 int /*<<< orphan*/  MEM_MODE ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i830_init_clock_gating(struct drm_i915_private *dev_priv)
{
	I915_WRITE(MEM_MODE,
		   _MASKED_BIT_ENABLE(MEM_DISPLAY_A_TRICKLE_FEED_DISABLE) |
		   _MASKED_BIT_ENABLE(MEM_DISPLAY_B_TRICKLE_FEED_DISABLE));
}