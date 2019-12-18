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

/* Variables and functions */
 int /*<<< orphan*/  CX25840_IR_REFCLK_FREQ ; 
 unsigned int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline unsigned int clock_divider_to_freq(unsigned int divider,
						 unsigned int rollovers)
{
	return DIV_ROUND_CLOSEST(CX25840_IR_REFCLK_FREQ,
				 (divider + 1) * rollovers);
}