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
struct slimpro_mbox_chan {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; scalar_t__ reg; } ;
struct mbox_chan {struct slimpro_mbox_chan* con_priv; } ;

/* Variables and functions */
 int MBOX_STATUS_ACK_MASK ; 
 int MBOX_STATUS_AVAIL_MASK ; 
 scalar_t__ REG_DB_STATMASK ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct slimpro_mbox_chan*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void slimpro_mbox_shutdown(struct mbox_chan *chan)
{
	struct slimpro_mbox_chan *mb_chan = chan->con_priv;
	u32 val;

	/* Mask doorbell status interrupt */
	val = readl(mb_chan->reg + REG_DB_STATMASK);
	val |= (MBOX_STATUS_ACK_MASK | MBOX_STATUS_AVAIL_MASK);
	writel(val, mb_chan->reg + REG_DB_STATMASK);

	devm_free_irq(mb_chan->dev, mb_chan->irq, mb_chan);
}