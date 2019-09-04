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
struct img_ir_timing_range {scalar_t__ max; scalar_t__ min; } ;

/* Variables and functions */

__attribute__((used)) static void img_ir_timing_defaults(struct img_ir_timing_range *range,
				   struct img_ir_timing_range *defaults)
{
	if (!range->min)
		range->min = defaults->min;
	if (!range->max)
		range->max = defaults->max;
}