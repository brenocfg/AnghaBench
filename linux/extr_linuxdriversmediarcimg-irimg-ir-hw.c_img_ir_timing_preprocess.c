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
struct img_ir_timing_range {unsigned int max; unsigned int min; } ;

/* Variables and functions */

__attribute__((used)) static void img_ir_timing_preprocess(struct img_ir_timing_range *range,
				     unsigned int unit)
{
	if (range->max < range->min)
		range->max = range->min;
	if (unit) {
		/* multiply by unit and convert to microseconds */
		range->min = (range->min*unit)/1000;
		range->max = (range->max*unit + 999)/1000; /* round up */
	}
}