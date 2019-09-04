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
 int /*<<< orphan*/  BM_TIMROT_TIMCTRLn_IRQ_EN ; 
 scalar_t__ HW_TIMROT_TIMCTRLn (int /*<<< orphan*/ ) ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mxs_timrot_base ; 

__attribute__((used)) static inline void timrot_irq_disable(void)
{
	__raw_writel(BM_TIMROT_TIMCTRLn_IRQ_EN, mxs_timrot_base +
		     HW_TIMROT_TIMCTRLn(0) + STMP_OFFSET_REG_CLR);
}