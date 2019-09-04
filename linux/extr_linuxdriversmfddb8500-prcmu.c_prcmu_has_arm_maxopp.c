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
 int PRCM_AVS_ISMODEENABLE_MASK ; 
 scalar_t__ PRCM_AVS_VARM_MAX_OPP ; 
 int readb (scalar_t__) ; 
 scalar_t__ tcdm_base ; 

bool prcmu_has_arm_maxopp(void)
{
	return (readb(tcdm_base + PRCM_AVS_VARM_MAX_OPP) &
		PRCM_AVS_ISMODEENABLE_MASK) == PRCM_AVS_ISMODEENABLE_MASK;
}