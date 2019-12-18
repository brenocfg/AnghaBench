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
typedef  unsigned short u32 ;
struct ipu_pre {unsigned int last_bufaddr; unsigned short safe_window_end; scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int IPU_PRE_CTRL_SDW_UPDATE ; 
 scalar_t__ IPU_PRE_CTRL_SET ; 
 scalar_t__ IPU_PRE_NEXT_BUF ; 
 scalar_t__ IPU_PRE_STORE_ENG_STATUS ; 
 unsigned short IPU_PRE_STORE_ENG_STATUS_STORE_BLOCK_Y_MASK ; 
 unsigned short IPU_PRE_STORE_ENG_STATUS_STORE_BLOCK_Y_SHIFT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 unsigned short readl (scalar_t__) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

void ipu_pre_update(struct ipu_pre *pre, unsigned int bufaddr)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(5);
	unsigned short current_yblock;
	u32 val;

	if (bufaddr == pre->last_bufaddr)
		return;

	writel(bufaddr, pre->regs + IPU_PRE_NEXT_BUF);
	pre->last_bufaddr = bufaddr;

	do {
		if (time_after(jiffies, timeout)) {
			dev_warn(pre->dev, "timeout waiting for PRE safe window\n");
			return;
		}

		val = readl(pre->regs + IPU_PRE_STORE_ENG_STATUS);
		current_yblock =
			(val >> IPU_PRE_STORE_ENG_STATUS_STORE_BLOCK_Y_SHIFT) &
			IPU_PRE_STORE_ENG_STATUS_STORE_BLOCK_Y_MASK;
	} while (current_yblock == 0 || current_yblock >= pre->safe_window_end);

	writel(IPU_PRE_CTRL_SDW_UPDATE, pre->regs + IPU_PRE_CTRL_SET);
}