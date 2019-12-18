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
struct gsc_dev {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ GSC_ENABLE ; 
 int /*<<< orphan*/  GSC_ENABLE_ON ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void gsc_hw_enable_control(struct gsc_dev *dev, bool on)
{
	u32 cfg = readl(dev->regs + GSC_ENABLE);

	if (on)
		cfg |= GSC_ENABLE_ON;
	else
		cfg &= ~GSC_ENABLE_ON;

	writel(cfg, dev->regs + GSC_ENABLE);
}