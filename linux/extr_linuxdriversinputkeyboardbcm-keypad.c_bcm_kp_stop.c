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
typedef  int /*<<< orphan*/  u32 ;
struct bcm_kp {scalar_t__ clk; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  KPCR_ENABLE ; 
 scalar_t__ KPCR_OFFSET ; 
 scalar_t__ KPICR0_OFFSET ; 
 scalar_t__ KPICR1_OFFSET ; 
 scalar_t__ KPIMR0_OFFSET ; 
 scalar_t__ KPIMR1_OFFSET ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void bcm_kp_stop(const struct bcm_kp *kp)
{
	u32 val;

	val = readl(kp->base + KPCR_OFFSET);
	val &= ~KPCR_ENABLE;
	writel(0, kp->base + KPCR_OFFSET);
	writel(0, kp->base + KPIMR0_OFFSET);
	writel(0, kp->base + KPIMR1_OFFSET);
	writel(0xFFFFFFFF, kp->base + KPICR0_OFFSET);
	writel(0xFFFFFFFF, kp->base + KPICR1_OFFSET);

	if (kp->clk)
		clk_disable_unprepare(kp->clk);
}