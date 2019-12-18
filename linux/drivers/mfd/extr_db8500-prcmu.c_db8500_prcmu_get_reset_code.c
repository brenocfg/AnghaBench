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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ PRCM_SW_RST_REASON ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 scalar_t__ tcdm_base ; 

u16 db8500_prcmu_get_reset_code(void)
{
	return readw(tcdm_base + PRCM_SW_RST_REASON);
}