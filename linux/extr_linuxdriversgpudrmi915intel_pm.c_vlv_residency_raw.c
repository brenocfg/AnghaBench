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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 scalar_t__ I915_READ_FW (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLV_COUNTER_CONTROL ; 
 int /*<<< orphan*/  VLV_COUNT_RANGE_HIGH ; 
 int /*<<< orphan*/  _MASKED_BIT_DISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 vlv_residency_raw(struct drm_i915_private *dev_priv,
			     const i915_reg_t reg)
{
	u32 lower, upper, tmp;
	int loop = 2;

	/*
	 * The register accessed do not need forcewake. We borrow
	 * uncore lock to prevent concurrent access to range reg.
	 */
	lockdep_assert_held(&dev_priv->uncore.lock);

	/*
	 * vlv and chv residency counters are 40 bits in width.
	 * With a control bit, we can choose between upper or lower
	 * 32bit window into this counter.
	 *
	 * Although we always use the counter in high-range mode elsewhere,
	 * userspace may attempt to read the value before rc6 is initialised,
	 * before we have set the default VLV_COUNTER_CONTROL value. So always
	 * set the high bit to be safe.
	 */
	I915_WRITE_FW(VLV_COUNTER_CONTROL,
		      _MASKED_BIT_ENABLE(VLV_COUNT_RANGE_HIGH));
	upper = I915_READ_FW(reg);
	do {
		tmp = upper;

		I915_WRITE_FW(VLV_COUNTER_CONTROL,
			      _MASKED_BIT_DISABLE(VLV_COUNT_RANGE_HIGH));
		lower = I915_READ_FW(reg);

		I915_WRITE_FW(VLV_COUNTER_CONTROL,
			      _MASKED_BIT_ENABLE(VLV_COUNT_RANGE_HIGH));
		upper = I915_READ_FW(reg);
	} while (upper != tmp && --loop);

	/*
	 * Everywhere else we always use VLV_COUNTER_CONTROL with the
	 * VLV_COUNT_RANGE_HIGH bit set - so it is safe to leave it set
	 * now.
	 */

	return lower | (u64)upper << 8;
}