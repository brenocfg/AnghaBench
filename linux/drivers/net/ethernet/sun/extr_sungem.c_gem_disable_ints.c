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
struct gem {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ GREG_IMASK ; 
 int GREG_STAT_NAPI ; 
 int GREG_STAT_TXDONE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void gem_disable_ints(struct gem *gp)
{
	/* Disable all interrupts, including TXDONE */
	writel(GREG_STAT_NAPI | GREG_STAT_TXDONE, gp->regs + GREG_IMASK);
	(void)readl(gp->regs + GREG_IMASK); /* write posting */
}