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
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 keystone_irq_readl(struct keystone_irq_device *kirq)
{
	int ret;
	u32 val = 0;

	ret = regmap_read(kirq->devctrl_regs, kirq->devctrl_offset, &val);
	if (ret < 0)
		dev_dbg(kirq->dev, "irq read failed ret(%d)\n", ret);
	return val;
}