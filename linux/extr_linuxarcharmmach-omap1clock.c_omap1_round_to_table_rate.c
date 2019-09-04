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
struct mpu_rate {long rate; int flags; unsigned long xtal; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {unsigned long rate; } ;

/* Variables and functions */
 long EINVAL ; 
 TYPE_1__* ck_ref_p ; 
 int cpu_mask ; 
 struct mpu_rate* omap1_rate_table ; 

long omap1_round_to_table_rate(struct clk *clk, unsigned long rate)
{
	/* Find the highest supported frequency <= rate */
	struct mpu_rate * ptr;
	long highest_rate;
	unsigned long ref_rate;

	ref_rate = ck_ref_p->rate;

	highest_rate = -EINVAL;

	for (ptr = omap1_rate_table; ptr->rate; ptr++) {
		if (!(ptr->flags & cpu_mask))
			continue;

		if (ptr->xtal != ref_rate)
			continue;

		highest_rate = ptr->rate;

		/* Can check only after xtal frequency check */
		if (ptr->rate <= rate)
			break;
	}

	return highest_rate;
}