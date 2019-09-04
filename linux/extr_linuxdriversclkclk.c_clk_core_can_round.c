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
struct clk_core {TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ round_rate; scalar_t__ determine_rate; } ;

/* Variables and functions */

__attribute__((used)) static bool clk_core_can_round(struct clk_core * const core)
{
	if (core->ops->determine_rate || core->ops->round_rate)
		return true;

	return false;
}