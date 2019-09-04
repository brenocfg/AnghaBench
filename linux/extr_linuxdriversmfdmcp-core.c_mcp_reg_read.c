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
struct mcp {int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct TYPE_2__ {unsigned int (* reg_read ) (struct mcp*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int stub1 (struct mcp*,unsigned int) ; 

unsigned int mcp_reg_read(struct mcp *mcp, unsigned int reg)
{
	unsigned long flags;
	unsigned int val;

	spin_lock_irqsave(&mcp->lock, flags);
	val = mcp->ops->reg_read(mcp, reg);
	spin_unlock_irqrestore(&mcp->lock, flags);

	return val;
}