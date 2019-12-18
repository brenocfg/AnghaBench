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
typedef  unsigned long u32 ;

/* Variables and functions */
 unsigned long VCO_MAX_RATE ; 
 unsigned long VCO_MIN_RATE ; 

__attribute__((used)) static u32 pll_14nm_kvco_slop(u32 vrate)
{
	u32 slop = 0;

	if (vrate > VCO_MIN_RATE && vrate <= 1800000000UL)
		slop =  600;
	else if (vrate > 1800000000UL && vrate < 2300000000UL)
		slop = 400;
	else if (vrate > 2300000000UL && vrate < VCO_MAX_RATE)
		slop = 280;

	return slop;
}