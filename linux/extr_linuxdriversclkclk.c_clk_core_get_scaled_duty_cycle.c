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
struct clk_duty {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct clk_core {struct clk_duty duty; } ;

/* Variables and functions */
 int clk_core_update_duty_cycle_nolock (struct clk_core*) ; 
 int /*<<< orphan*/  clk_prepare_lock () ; 
 int /*<<< orphan*/  clk_prepare_unlock () ; 
 int mult_frac (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_core_get_scaled_duty_cycle(struct clk_core *core,
					  unsigned int scale)
{
	struct clk_duty *duty = &core->duty;
	int ret;

	clk_prepare_lock();

	ret = clk_core_update_duty_cycle_nolock(core);
	if (!ret)
		ret = mult_frac(scale, duty->num, duty->den);

	clk_prepare_unlock();

	return ret;
}