#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pss_ctl_reg; } ;
struct bfa_ioc {TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __PSS_LPU0_RESET ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_lpu_start(struct bfa_ioc *ioc)
{
	u32	pss_ctl;

	/**
	 * Take processor out of reset.
	 */
	pss_ctl = readl(ioc->ioc_regs.pss_ctl_reg);
	pss_ctl &= ~__PSS_LPU0_RESET;

	writel(pss_ctl, ioc->ioc_regs.pss_ctl_reg);
}