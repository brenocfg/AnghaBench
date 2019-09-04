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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 scalar_t__* CSR_TIMER1_CLR ; 
 int* CSR_TIMER1_CNTL ; 
 int* CSR_TIMER1_LOAD ; 
 int HZ ; 
 int TIMER_CNTL_AUTORELOAD ; 
 int TIMER_CNTL_DIV16 ; 
 int TIMER_CNTL_ENABLE ; 
 int mem_fclk_21285 ; 

__attribute__((used)) static int ckevt_dc21285_set_periodic(struct clock_event_device *c)
{
	*CSR_TIMER1_CLR = 0;
	*CSR_TIMER1_LOAD = (mem_fclk_21285 + 8 * HZ) / (16 * HZ);
	*CSR_TIMER1_CNTL = TIMER_CNTL_ENABLE | TIMER_CNTL_AUTORELOAD |
			   TIMER_CNTL_DIV16;
	return 0;
}