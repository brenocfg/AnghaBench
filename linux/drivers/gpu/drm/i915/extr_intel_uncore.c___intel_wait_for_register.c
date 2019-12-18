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
typedef  int u32 ;
struct intel_uncore {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  reg_value ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  FW_REG_READ ; 
 int __intel_wait_for_register_fw (struct intel_uncore*,int /*<<< orphan*/ ,int,int,unsigned int,int /*<<< orphan*/ ,int*) ; 
 int __wait_for (int,int,unsigned int,int,int) ; 
 unsigned int intel_uncore_forcewake_for_reg (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get__locked (struct intel_uncore*,unsigned int) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put__locked (struct intel_uncore*,unsigned int) ; 
 int intel_uncore_read_notrace (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep_if (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_i915_reg_rw (int,int /*<<< orphan*/ ,int,int,int) ; 

int __intel_wait_for_register(struct intel_uncore *uncore,
			      i915_reg_t reg,
			      u32 mask,
			      u32 value,
			      unsigned int fast_timeout_us,
			      unsigned int slow_timeout_ms,
			      u32 *out_value)
{
	unsigned fw =
		intel_uncore_forcewake_for_reg(uncore, reg, FW_REG_READ);
	u32 reg_value;
	int ret;

	might_sleep_if(slow_timeout_ms);

	spin_lock_irq(&uncore->lock);
	intel_uncore_forcewake_get__locked(uncore, fw);

	ret = __intel_wait_for_register_fw(uncore,
					   reg, mask, value,
					   fast_timeout_us, 0, &reg_value);

	intel_uncore_forcewake_put__locked(uncore, fw);
	spin_unlock_irq(&uncore->lock);

	if (ret && slow_timeout_ms)
		ret = __wait_for(reg_value = intel_uncore_read_notrace(uncore,
								       reg),
				 (reg_value & mask) == value,
				 slow_timeout_ms * 1000, 10, 1000);

	/* just trace the final value */
	trace_i915_reg_rw(false, reg, reg_value, sizeof(reg_value), true);

	if (out_value)
		*out_value = reg_value;

	return ret;
}