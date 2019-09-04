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
struct idt77252_dev {int /*<<< orphan*/  cmd_lock; } ;

/* Variables and functions */
 unsigned long SAR_CMD_READ_SRAM ; 
 int /*<<< orphan*/  SAR_REG_CMD ; 
 int /*<<< orphan*/  SAR_REG_DR0 ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  waitfor_idle (struct idt77252_dev*) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
read_sram(struct idt77252_dev *card, unsigned long addr)
{
	unsigned long flags;
	u32 value;

	spin_lock_irqsave(&card->cmd_lock, flags);
	writel(SAR_CMD_READ_SRAM | (addr << 2), SAR_REG_CMD);
	waitfor_idle(card);
	value = readl(SAR_REG_DR0);
	spin_unlock_irqrestore(&card->cmd_lock, flags);
	return value;
}