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
struct fimc_lite {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ FLITE_REG_CIODMAFMT ; 
 int /*<<< orphan*/  FLITE_REG_CIODMAFMT_PACK12 ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void flite_hw_set_pack12(struct fimc_lite *dev, int on)
{
	u32 cfg = readl(dev->regs + FLITE_REG_CIODMAFMT);

	cfg &= ~FLITE_REG_CIODMAFMT_PACK12;

	if (on)
		cfg |= FLITE_REG_CIODMAFMT_PACK12;

	writel(cfg, dev->regs + FLITE_REG_CIODMAFMT);
}