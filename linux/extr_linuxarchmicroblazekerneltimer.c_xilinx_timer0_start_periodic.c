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
 scalar_t__ TCSR0 ; 
 unsigned long TCSR_ARHT ; 
 unsigned long TCSR_ENIT ; 
 unsigned long TCSR_ENT ; 
 unsigned long TCSR_LOAD ; 
 unsigned long TCSR_TINT ; 
 unsigned long TCSR_UDT ; 
 scalar_t__ TLR0 ; 
 scalar_t__ timer_baseaddr ; 
 int /*<<< orphan*/  write_fn (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline void xilinx_timer0_start_periodic(unsigned long load_val)
{
	if (!load_val)
		load_val = 1;
	/* loading value to timer reg */
	write_fn(load_val, timer_baseaddr + TLR0);

	/* load the initial value */
	write_fn(TCSR_LOAD, timer_baseaddr + TCSR0);

	/* see timer data sheet for detail
	 * !ENALL - don't enable 'em all
	 * !PWMA - disable pwm
	 * TINT - clear interrupt status
	 * ENT- enable timer itself
	 * ENIT - enable interrupt
	 * !LOAD - clear the bit to let go
	 * ARHT - auto reload
	 * !CAPT - no external trigger
	 * !GENT - no external signal
	 * UDT - set the timer as down counter
	 * !MDT0 - generate mode
	 */
	write_fn(TCSR_TINT|TCSR_ENIT|TCSR_ENT|TCSR_ARHT|TCSR_UDT,
		 timer_baseaddr + TCSR0);
}