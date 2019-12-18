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
 int /*<<< orphan*/  PRCM_DDR_SUBSYS_APE_MINBW ; 
 int readb (int /*<<< orphan*/ ) ; 

int db8500_prcmu_get_ddr_opp(void)
{
	return readb(PRCM_DDR_SUBSYS_APE_MINBW);
}