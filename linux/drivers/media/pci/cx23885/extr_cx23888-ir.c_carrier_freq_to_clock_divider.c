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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CX23888_IR_REFCLK_FREQ ; 
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  count_to_clock_divider (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 carrier_freq_to_clock_divider(unsigned int freq)
{
	return count_to_clock_divider(
			  DIV_ROUND_CLOSEST(CX23888_IR_REFCLK_FREQ, freq * 16));
}