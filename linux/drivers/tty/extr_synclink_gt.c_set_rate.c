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
struct slgt_info {unsigned int base_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDR ; 
 int /*<<< orphan*/  wr_reg16 (struct slgt_info*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void set_rate(struct slgt_info *info, u32 rate)
{
	unsigned int div;
	unsigned int osc = info->base_clock;

	/* div = osc/rate - 1
	 *
	 * Round div up if osc/rate is not integer to
	 * force to next slowest rate.
	 */

	if (rate) {
		div = osc/rate;
		if (!(osc % rate) && div)
			div--;
		wr_reg16(info, BDR, (unsigned short)div);
	}
}