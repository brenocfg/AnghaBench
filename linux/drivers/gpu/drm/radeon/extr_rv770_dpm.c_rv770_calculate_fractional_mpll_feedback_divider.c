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
struct atom_clock_dividers {int post_div; int ref_div; } ;

/* Variables and functions */

__attribute__((used)) static void rv770_calculate_fractional_mpll_feedback_divider(u32 memory_clock,
							     u32 reference_clock,
							     bool gddr5,
							     struct atom_clock_dividers *dividers,
							     u32 *clkf,
							     u32 *clkfrac)
{
	u32 post_divider, reference_divider, feedback_divider8;
	u32 fyclk;

	if (gddr5)
		fyclk = (memory_clock * 8) / 2;
	else
		fyclk = (memory_clock * 4) / 2;

	post_divider = dividers->post_div;
	reference_divider = dividers->ref_div;

	feedback_divider8 =
		(8 * fyclk * reference_divider * post_divider) / reference_clock;

	*clkf = feedback_divider8 / 8;
	*clkfrac = feedback_divider8 % 8;
}