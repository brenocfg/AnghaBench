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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ cur_delay; scalar_t__ max_delay; scalar_t__ min_delay; } ;
struct drm_i915_private {TYPE_1__ ips; } ;

/* Variables and functions */
 scalar_t__ I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MEMINTRSTS ; 
 scalar_t__ MEMINT_EVAL_CHG ; 
 int /*<<< orphan*/  RCBMAXAVG ; 
 int /*<<< orphan*/  RCBMINAVG ; 
 int /*<<< orphan*/  RCPREVBSYTDNAVG ; 
 int /*<<< orphan*/  RCPREVBSYTUPAVG ; 
 scalar_t__ ironlake_set_drps (struct drm_i915_private*,scalar_t__) ; 
 int /*<<< orphan*/  mchdev_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ironlake_rps_change_irq_handler(struct drm_i915_private *dev_priv)
{
	u32 busy_up, busy_down, max_avg, min_avg;
	u8 new_delay;

	spin_lock(&mchdev_lock);

	I915_WRITE16(MEMINTRSTS, I915_READ(MEMINTRSTS));

	new_delay = dev_priv->ips.cur_delay;

	I915_WRITE16(MEMINTRSTS, MEMINT_EVAL_CHG);
	busy_up = I915_READ(RCPREVBSYTUPAVG);
	busy_down = I915_READ(RCPREVBSYTDNAVG);
	max_avg = I915_READ(RCBMAXAVG);
	min_avg = I915_READ(RCBMINAVG);

	/* Handle RCS change request from hw */
	if (busy_up > max_avg) {
		if (dev_priv->ips.cur_delay != dev_priv->ips.max_delay)
			new_delay = dev_priv->ips.cur_delay - 1;
		if (new_delay < dev_priv->ips.max_delay)
			new_delay = dev_priv->ips.max_delay;
	} else if (busy_down < min_avg) {
		if (dev_priv->ips.cur_delay != dev_priv->ips.min_delay)
			new_delay = dev_priv->ips.cur_delay + 1;
		if (new_delay > dev_priv->ips.min_delay)
			new_delay = dev_priv->ips.min_delay;
	}

	if (ironlake_set_drps(dev_priv, new_delay))
		dev_priv->ips.cur_delay = new_delay;

	spin_unlock(&mchdev_lock);

	return;
}