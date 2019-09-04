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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long AC97_DIV ; 

__attribute__((used)) static unsigned long clk_pxa3xx_ac97_get_rate(struct clk_hw *hw,
					     unsigned long parent_rate)
{
	unsigned long ac97_div, rate;

	ac97_div = AC97_DIV;

	/* This may loose precision for some rates but won't for the
	 * standard 24.576MHz.
	 */
	rate = parent_rate / 2;
	rate /= ((ac97_div >> 12) & 0x7fff);
	rate *= (ac97_div & 0xfff);

	return rate;
}