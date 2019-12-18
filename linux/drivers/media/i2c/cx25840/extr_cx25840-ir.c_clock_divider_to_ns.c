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
 int CX25840_IR_REFCLK_FREQ ; 
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int) ; 

__attribute__((used)) static inline unsigned int clock_divider_to_ns(unsigned int divider)
{
	/* Period of the Rx or Tx clock in ns */
	return DIV_ROUND_CLOSEST((divider + 1) * 1000,
				 CX25840_IR_REFCLK_FREQ / 1000000);
}