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
typedef  int u32 ;
struct whc {int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ WUSBCMD ; 
 int le_readl (scalar_t__) ; 
 int /*<<< orphan*/  le_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void whc_write_wusbcmd(struct whc *whc, u32 mask, u32 val)
{
	unsigned long flags;
	u32 cmd;

	spin_lock_irqsave(&whc->lock, flags);

	cmd = le_readl(whc->base + WUSBCMD);
	cmd = (cmd & ~mask) | val;
	le_writel(cmd, whc->base + WUSBCMD);

	spin_unlock_irqrestore(&whc->lock, flags);
}