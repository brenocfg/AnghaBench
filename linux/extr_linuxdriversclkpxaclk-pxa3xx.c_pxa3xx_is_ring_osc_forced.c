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
 unsigned long ACCR_D0CS ; 
 unsigned long ACSR ; 

__attribute__((used)) static bool pxa3xx_is_ring_osc_forced(void)
{
	unsigned long acsr = ACSR;

	return acsr & ACCR_D0CS;
}