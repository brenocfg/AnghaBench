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
 int PL080_CONTROL_DST_AHB2 ; 
 int PL080_CONTROL_DST_INCR ; 
 int PL080_CONTROL_PROT_MASK ; 
 int PL080_CONTROL_PROT_SYS ; 
 int PL080_CONTROL_SRC_AHB2 ; 
 int PL080_CONTROL_SRC_INCR ; 

__attribute__((used)) static u32 pl08x_cctl(u32 cctl)
{
	cctl &= ~(PL080_CONTROL_SRC_AHB2 | PL080_CONTROL_DST_AHB2 |
		  PL080_CONTROL_SRC_INCR | PL080_CONTROL_DST_INCR |
		  PL080_CONTROL_PROT_MASK);

	/* Access the cell in privileged mode, non-bufferable, non-cacheable */
	return cctl | PL080_CONTROL_PROT_SYS;
}