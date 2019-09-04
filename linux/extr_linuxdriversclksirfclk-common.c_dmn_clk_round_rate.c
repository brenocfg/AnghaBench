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
struct clk_hw {TYPE_1__* init; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static long dmn_clk_round_rate(struct clk_hw *hw, unsigned long rate,
	unsigned long *parent_rate)
{
	unsigned long fin;
	unsigned ratio, wait, hold;
	unsigned bits = (strcmp(hw->init->name, "mem") == 0) ? 3 : 4;

	fin = *parent_rate;
	ratio = fin / rate;

	if (ratio < 2)
		ratio = 2;
	if (ratio > BIT(bits + 1))
		ratio = BIT(bits + 1);

	wait = (ratio >> 1) - 1;
	hold = ratio - wait - 2;

	return fin / (wait + hold + 2);
}