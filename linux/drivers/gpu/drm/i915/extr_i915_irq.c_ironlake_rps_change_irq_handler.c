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
struct intel_uncore {int dummy; } ;
struct TYPE_2__ {scalar_t__ cur_delay; scalar_t__ max_delay; scalar_t__ min_delay; } ;
struct drm_i915_private {TYPE_1__ ips; struct intel_uncore uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMINTRSTS ; 
 scalar_t__ MEMINT_EVAL_CHG ; 
 int /*<<< orphan*/  RCBMAXAVG ; 
 int /*<<< orphan*/  RCBMINAVG ; 
 int /*<<< orphan*/  RCPREVBSYTDNAVG ; 
 int /*<<< orphan*/  RCPREVBSYTUPAVG ; 
 scalar_t__ intel_uncore_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write16 (struct intel_uncore*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ironlake_set_drps (struct drm_i915_private*,scalar_t__) ; 
 int /*<<< orphan*/  mchdev_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ironlake_rps_change_irq_handler(struct drm_i915_private *dev_priv)
{
	struct intel_uncore *uncore = &dev_priv->uncore;
	u32 busy_up, busy_down, max_avg, min_avg;
	u8 new_delay;

	spin_lock(&mchdev_lock);

	intel_uncore_write16(uncore,
			     MEMINTRSTS,
			     intel_uncore_read(uncore, MEMINTRSTS));

	new_delay = dev_priv->ips.cur_delay;

	intel_uncore_write16(uncore, MEMINTRSTS, MEMINT_EVAL_CHG);
	busy_up = intel_uncore_read(uncore, RCPREVBSYTUPAVG);
	busy_down = intel_uncore_read(uncore, RCPREVBSYTDNAVG);
	max_avg = intel_uncore_read(uncore, RCBMAXAVG);
	min_avg = intel_uncore_read(uncore, RCBMINAVG);

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