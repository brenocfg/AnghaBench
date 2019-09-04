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
struct bcma_drv_cc {int capabilities; } ;

/* Variables and functions */
 int BCMA_CC_CAP_PMU ; 
 int bcma_pmu_get_alp_clock (struct bcma_drv_cc*) ; 

u32 bcma_chipco_get_alp_clock(struct bcma_drv_cc *cc)
{
	if (cc->capabilities & BCMA_CC_CAP_PMU)
		return bcma_pmu_get_alp_clock(cc);

	return 20000000;
}