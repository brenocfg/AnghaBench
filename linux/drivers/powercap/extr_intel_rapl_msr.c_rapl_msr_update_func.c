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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct reg_action {scalar_t__ err; int /*<<< orphan*/  value; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 scalar_t__ rdmsrl_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ wrmsrl_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rapl_msr_update_func(void *info)
{
	struct reg_action *ra = info;
	u32 msr = (u32)ra->reg;
	u64 val;

	ra->err = rdmsrl_safe(msr, &val);
	if (ra->err)
		return;

	val &= ~ra->mask;
	val |= ra->value;

	ra->err = wrmsrl_safe(msr, val);
}