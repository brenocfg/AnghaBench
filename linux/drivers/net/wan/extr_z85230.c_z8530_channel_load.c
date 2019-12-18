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
typedef  int u8 ;
struct z8530_channel {int* regs; int mtu; int sync; int /*<<< orphan*/  lock; int /*<<< orphan*/  status; scalar_t__ count; scalar_t__ max; int /*<<< orphan*/ * tx_next_skb; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/ * skb; int /*<<< orphan*/  rx_function; } ;

/* Variables and functions */
 int /*<<< orphan*/  R0 ; 
 size_t R15 ; 
 size_t R3 ; 
 int RxENABLE ; 
 int /*<<< orphan*/  read_zsreg (struct z8530_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  write_zsreg (struct z8530_channel*,size_t,int) ; 
 int /*<<< orphan*/  z8530_null_rx ; 

int z8530_channel_load(struct z8530_channel *c, u8 *rtable)
{
	unsigned long flags;

	spin_lock_irqsave(c->lock, flags);

	while(*rtable!=255)
	{
		int reg=*rtable++;
		if(reg>0x0F)
			write_zsreg(c, R15, c->regs[15]|1);
		write_zsreg(c, reg&0x0F, *rtable);
		if(reg>0x0F)
			write_zsreg(c, R15, c->regs[15]&~1);
		c->regs[reg]=*rtable++;
	}
	c->rx_function=z8530_null_rx;
	c->skb=NULL;
	c->tx_skb=NULL;
	c->tx_next_skb=NULL;
	c->mtu=1500;
	c->max=0;
	c->count=0;
	c->status=read_zsreg(c, R0);
	c->sync=1;
	write_zsreg(c, R3, c->regs[R3]|RxENABLE);

	spin_unlock_irqrestore(c->lock, flags);
	return 0;
}