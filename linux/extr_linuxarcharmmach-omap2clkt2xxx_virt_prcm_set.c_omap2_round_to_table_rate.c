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
struct prcm_config {long mpu_speed; int flags; scalar_t__ xtal_speed; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 int cpu_mask ; 
 struct prcm_config* rate_table ; 
 scalar_t__ sys_ck_rate ; 

long omap2_round_to_table_rate(struct clk_hw *hw, unsigned long rate,
			       unsigned long *parent_rate)
{
	const struct prcm_config *ptr;
	long highest_rate;

	highest_rate = -EINVAL;

	for (ptr = rate_table; ptr->mpu_speed; ptr++) {
		if (!(ptr->flags & cpu_mask))
			continue;
		if (ptr->xtal_speed != sys_ck_rate)
			continue;

		highest_rate = ptr->mpu_speed;

		/* Can check only after xtal frequency check */
		if (ptr->mpu_speed <= rate)
			break;
	}
	return highest_rate;
}