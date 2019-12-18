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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int last_time2; scalar_t__ last_count2; int gfx_power; } ;
struct drm_i915_private {TYPE_1__ ips; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFXEC ; 
 scalar_t__ I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NSEC_PER_MSEC ; 
 int div_u64 (int,int) ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int ktime_get_raw_ns () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mchdev_lock ; 

__attribute__((used)) static void __i915_update_gfx_val(struct drm_i915_private *dev_priv)
{
	u64 now, diff, diffms;
	u32 count;

	lockdep_assert_held(&mchdev_lock);

	now = ktime_get_raw_ns();
	diffms = now - dev_priv->ips.last_time2;
	do_div(diffms, NSEC_PER_MSEC);

	/* Don't divide by 0 */
	if (!diffms)
		return;

	count = I915_READ(GFXEC);

	if (count < dev_priv->ips.last_count2) {
		diff = ~0UL - dev_priv->ips.last_count2;
		diff += count;
	} else {
		diff = count - dev_priv->ips.last_count2;
	}

	dev_priv->ips.last_count2 = count;
	dev_priv->ips.last_time2 = now;

	/* More magic constants... */
	diff = diff * 1181;
	diff = div_u64(diff, diffms * 10);
	dev_priv->ips.gfx_power = diff;
}