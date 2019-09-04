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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_START (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_TAIL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_unused_ring(struct drm_i915_private *dev_priv, u32 base)
{
	I915_WRITE(RING_CTL(base), 0);
	I915_WRITE(RING_HEAD(base), 0);
	I915_WRITE(RING_TAIL(base), 0);
	I915_WRITE(RING_START(base), 0);
}