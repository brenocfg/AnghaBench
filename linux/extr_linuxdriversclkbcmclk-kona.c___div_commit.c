#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ccu_data {int dummy; } ;
struct bcm_clk_trig {int dummy; } ;
struct bcm_clk_gate {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  width; int /*<<< orphan*/  shift; int /*<<< orphan*/  scaled_div; } ;
struct TYPE_4__ {TYPE_1__ s; } ;
struct bcm_clk_div {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_SCALED_DIV_VALUE ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  __ccu_read (struct ccu_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ccu_write (struct ccu_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clk_gate (struct ccu_data*,struct bcm_clk_gate*,int) ; 
 int /*<<< orphan*/  __clk_trigger (struct ccu_data*,struct bcm_clk_trig*) ; 
 int __is_clk_gate_enabled (struct ccu_data*,struct bcm_clk_gate*) ; 
 int /*<<< orphan*/  bitfield_extract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitfield_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  divider (struct bcm_clk_div*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  divider_is_fixed (struct bcm_clk_div*) ; 
 int /*<<< orphan*/  scaled_div_value (struct bcm_clk_div*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __div_commit(struct ccu_data *ccu, struct bcm_clk_gate *gate,
			struct bcm_clk_div *div, struct bcm_clk_trig *trig)
{
	bool enabled;
	u32 reg_div;
	u32 reg_val;
	int ret = 0;

	BUG_ON(divider_is_fixed(div));

	/*
	 * If we're just initializing the divider, and no initial
	 * state was defined in the device tree, we just find out
	 * what its current value is rather than updating it.
	 */
	if (div->u.s.scaled_div == BAD_SCALED_DIV_VALUE) {
		reg_val = __ccu_read(ccu, div->u.s.offset);
		reg_div = bitfield_extract(reg_val, div->u.s.shift,
						div->u.s.width);
		div->u.s.scaled_div = scaled_div_value(div, reg_div);

		return 0;
	}

	/* Convert the scaled divisor to the value we need to record */
	reg_div = divider(div, div->u.s.scaled_div);

	/* Clock needs to be enabled before changing the rate */
	enabled = __is_clk_gate_enabled(ccu, gate);
	if (!enabled && !__clk_gate(ccu, gate, true)) {
		ret = -ENXIO;
		goto out;
	}

	/* Replace the divider value and record the result */
	reg_val = __ccu_read(ccu, div->u.s.offset);
	reg_val = bitfield_replace(reg_val, div->u.s.shift, div->u.s.width,
					reg_div);
	__ccu_write(ccu, div->u.s.offset, reg_val);

	/* If the trigger fails we still want to disable the gate */
	if (!__clk_trigger(ccu, trig))
		ret = -EIO;

	/* Disable the clock again if it was disabled to begin with */
	if (!enabled && !__clk_gate(ccu, gate, false))
		ret = ret ? ret : -ENXIO;	/* return first error */
out:
	return ret;
}