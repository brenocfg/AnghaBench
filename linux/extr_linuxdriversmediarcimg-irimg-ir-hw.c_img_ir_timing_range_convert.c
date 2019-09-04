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
struct img_ir_timing_range {unsigned int min; unsigned int max; } ;

/* Variables and functions */

__attribute__((used)) static void img_ir_timing_range_convert(struct img_ir_timing_range *out,
					const struct img_ir_timing_range *in,
					unsigned int tolerance,
					unsigned long clock_hz,
					unsigned int shift)
{
	unsigned int min = in->min;
	unsigned int max = in->max;
	/* add a tolerance */
	min = min - (min*tolerance >> 7);
	max = max + (max*tolerance >> 7);
	/* convert from microseconds into clock cycles */
	min = min*clock_hz / 1000000;
	max = (max*clock_hz + 999999) / 1000000; /* round up */
	/* apply shift and copy to output */
	out->min = min >> shift;
	out->max = (max + ((1 << shift) - 1)) >> shift; /* round up */
}