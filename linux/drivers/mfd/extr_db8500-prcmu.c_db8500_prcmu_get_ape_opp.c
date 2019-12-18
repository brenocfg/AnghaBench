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
 scalar_t__ PRCM_ACK_MB1_CURRENT_APE_OPP ; 
 int readb (scalar_t__) ; 
 scalar_t__ tcdm_base ; 

int db8500_prcmu_get_ape_opp(void)
{
	return readb(tcdm_base + PRCM_ACK_MB1_CURRENT_APE_OPP);
}