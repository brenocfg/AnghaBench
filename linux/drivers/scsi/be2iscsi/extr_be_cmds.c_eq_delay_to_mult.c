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
typedef  int u32 ;

/* Variables and functions */
 int const MAX_INTR_RATE ; 
 int min (int,int) ; 

__attribute__((used)) static u32 eq_delay_to_mult(u32 usec_delay)
{
#define MAX_INTR_RATE 651042
	const u32 round = 10;
	u32 multiplier;

	if (usec_delay == 0)
		multiplier = 0;
	else {
		u32 interrupt_rate = 1000000 / usec_delay;
		if (interrupt_rate == 0)
			multiplier = 1023;
		else {
			multiplier = (MAX_INTR_RATE - interrupt_rate) * round;
			multiplier /= interrupt_rate;
			multiplier = (multiplier + round / 2) / round;
			multiplier = min(multiplier, (u32) 1023);
		}
	}
	return multiplier;
}