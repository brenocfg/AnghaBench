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
 int /*<<< orphan*/  PRCM_APE_SOFTRST ; 
 scalar_t__ PRCM_SW_RST_REASON ; 
 scalar_t__ tcdm_base ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

void db8500_prcmu_system_reset(u16 reset_code)
{
	writew(reset_code, (tcdm_base + PRCM_SW_RST_REASON));
	writel(1, PRCM_APE_SOFTRST);
}