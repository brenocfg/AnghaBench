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
struct TYPE_2__ {int /*<<< orphan*/  epoch; } ;
struct drm_i915_private {TYPE_1__ gt; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
same_epoch(struct drm_i915_private *i915, unsigned int epoch)
{
	/*
	 * There is a small chance that the epoch wrapped since we started
	 * sleeping. If we assume that epoch is at least a u32, then it will
	 * take at least 2^32 * 100ms for it to wrap, or about 326 years.
	 */
	return epoch == READ_ONCE(i915->gt.epoch);
}