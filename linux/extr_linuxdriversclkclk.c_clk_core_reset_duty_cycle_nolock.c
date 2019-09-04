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
struct TYPE_2__ {int num; int den; } ;
struct clk_core {TYPE_1__ duty; } ;

/* Variables and functions */

__attribute__((used)) static void clk_core_reset_duty_cycle_nolock(struct clk_core *core)
{
	/* Assume a default value of 50% */
	core->duty.num = 1;
	core->duty.den = 2;
}