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
 int /*<<< orphan*/  CCM_CCGRx (int) ; 
 int /*<<< orphan*/  CCM_CSCDR1 ; 
 int /*<<< orphan*/  CCM_CSCDR2 ; 
 int /*<<< orphan*/  CCM_CSCDR3 ; 
 int /*<<< orphan*/  CCM_CSCMR1 ; 
 int /*<<< orphan*/  CCM_CSCMR2 ; 
 int /*<<< orphan*/ * ccgr ; 
 int /*<<< orphan*/  cscdr1 ; 
 int /*<<< orphan*/  cscdr2 ; 
 int /*<<< orphan*/  cscdr3 ; 
 int /*<<< orphan*/  cscmr1 ; 
 int /*<<< orphan*/  cscmr2 ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vf610_clk_resume(void)
{
	int i;

	writel_relaxed(cscmr1, CCM_CSCMR1);
	writel_relaxed(cscmr2, CCM_CSCMR2);

	writel_relaxed(cscdr1, CCM_CSCDR1);
	writel_relaxed(cscdr2, CCM_CSCDR2);
	writel_relaxed(cscdr3, CCM_CSCDR3);

	for (i = 0; i < 12; i++)
		writel_relaxed(ccgr[i], CCM_CCGRx(i));
}