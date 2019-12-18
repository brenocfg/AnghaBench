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
struct keystone_irq_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  devctrl_offset; int /*<<< orphan*/  devctrl_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
keystone_irq_writel(struct keystone_irq_device *kirq, u32 value)
{
	int ret;

	ret = regmap_write(kirq->devctrl_regs, kirq->devctrl_offset, value);
	if (ret < 0)
		dev_dbg(kirq->dev, "irq write failed ret(%d)\n", ret);
}