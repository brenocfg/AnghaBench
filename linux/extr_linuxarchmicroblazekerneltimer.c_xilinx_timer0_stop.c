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
 int TCSR_ENT ; 
 int read_fn (scalar_t__) ; 
 scalar_t__ timer_baseaddr ; 
 int /*<<< orphan*/  write_fn (int,scalar_t__) ; 

__attribute__((used)) static inline void xilinx_timer0_stop(void)
{
	write_fn(read_fn(timer_baseaddr + TCSR0) & ~TCSR_ENT,
		 timer_baseaddr + TCSR0);
}