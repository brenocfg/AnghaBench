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
 unsigned long* pmcsel_mask ; 
 unsigned long* pmcsel_shift ; 

__attribute__((used)) static void mpc7450_disable_pmc(unsigned int pmc, unsigned long mmcr[])
{
	if (pmc <= 1)
		mmcr[0] &= ~(pmcsel_mask[pmc] << pmcsel_shift[pmc]);
	else
		mmcr[1] &= ~(pmcsel_mask[pmc] << pmcsel_shift[pmc]);
}