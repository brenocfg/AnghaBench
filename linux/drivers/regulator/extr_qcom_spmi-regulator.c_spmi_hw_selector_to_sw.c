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
typedef  unsigned int u8 ;
struct spmi_voltage_range {unsigned int set_point_min_uV; unsigned int min_uV; unsigned int step_uV; unsigned int set_point_max_uV; scalar_t__ n_voltages; } ;
struct spmi_regulator {TYPE_1__* set_points; } ;
struct TYPE_2__ {int count; struct spmi_voltage_range* range; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int spmi_hw_selector_to_sw(struct spmi_regulator *vreg, u8 hw_sel,
				  const struct spmi_voltage_range *range)
{
	unsigned sw_sel = 0;
	unsigned offset, max_hw_sel;
	const struct spmi_voltage_range *r = vreg->set_points->range;
	const struct spmi_voltage_range *end = r + vreg->set_points->count;

	for (; r < end; r++) {
		if (r == range && range->n_voltages) {
			/*
			 * hardware selectors between set point min and real
			 * min and between set point max and real max are
			 * invalid so we return an error if they're
			 * programmed into the hardware
			 */
			offset = range->set_point_min_uV - range->min_uV;
			offset /= range->step_uV;
			if (hw_sel < offset)
				return -EINVAL;

			max_hw_sel = range->set_point_max_uV - range->min_uV;
			max_hw_sel /= range->step_uV;
			if (hw_sel > max_hw_sel)
				return -EINVAL;

			return sw_sel + hw_sel - offset;
		}
		sw_sel += r->n_voltages;
	}

	return -EINVAL;
}