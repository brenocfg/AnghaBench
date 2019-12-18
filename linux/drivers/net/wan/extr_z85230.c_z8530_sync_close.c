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
typedef  int /*<<< orphan*/  u8 ;
struct z8530_channel {int /*<<< orphan*/  lock; int /*<<< orphan*/ * regs; scalar_t__ sync; scalar_t__ max; int /*<<< orphan*/ * irqs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R0 ; 
 size_t R3 ; 
 int /*<<< orphan*/  read_zsreg (struct z8530_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  write_zsreg (struct z8530_channel*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  z8530_nop ; 
 int /*<<< orphan*/  z8530_rtsdtr (struct z8530_channel*,int /*<<< orphan*/ ) ; 

int z8530_sync_close(struct net_device *dev, struct z8530_channel *c)
{
	u8 chk;
	unsigned long flags;
	
	spin_lock_irqsave(c->lock, flags);
	c->irqs = &z8530_nop;
	c->max = 0;
	c->sync = 0;
	
	chk=read_zsreg(c,R0);
	write_zsreg(c, R3, c->regs[R3]);
	z8530_rtsdtr(c,0);

	spin_unlock_irqrestore(c->lock, flags);
	return 0;
}