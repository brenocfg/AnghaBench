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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct macb {int caps; TYPE_1__* queues; } ;
struct ethtool_regs {int version; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_head; int /*<<< orphan*/  tx_tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMACFG ; 
 int /*<<< orphan*/  IMR ; 
 int MACB_CAPS_USRIO_DISABLED ; 
 int MACB_GREGS_VERSION ; 
 int MACB_REV_SIZE ; 
 int /*<<< orphan*/  MID ; 
 int /*<<< orphan*/  NCFGR ; 
 int /*<<< orphan*/  NCR ; 
 int /*<<< orphan*/  NSR ; 
 int /*<<< orphan*/  RBQP ; 
 int /*<<< orphan*/  RSR ; 
 int /*<<< orphan*/  TBQP ; 
 int /*<<< orphan*/  TSR ; 
 int /*<<< orphan*/  USRIO ; 
 int gem_readl (struct macb*,int /*<<< orphan*/ ) ; 
 scalar_t__ macb_is_gem (struct macb*) ; 
 int macb_or_gem_readl (struct macb*,int /*<<< orphan*/ ) ; 
 int macb_readl (struct macb*,int /*<<< orphan*/ ) ; 
 int macb_tx_dma (TYPE_1__*,unsigned int) ; 
 unsigned int macb_tx_ring_wrap (struct macb*,int /*<<< orphan*/ ) ; 
 struct macb* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void macb_get_regs(struct net_device *dev, struct ethtool_regs *regs,
			  void *p)
{
	struct macb *bp = netdev_priv(dev);
	unsigned int tail, head;
	u32 *regs_buff = p;

	regs->version = (macb_readl(bp, MID) & ((1 << MACB_REV_SIZE) - 1))
			| MACB_GREGS_VERSION;

	tail = macb_tx_ring_wrap(bp, bp->queues[0].tx_tail);
	head = macb_tx_ring_wrap(bp, bp->queues[0].tx_head);

	regs_buff[0]  = macb_readl(bp, NCR);
	regs_buff[1]  = macb_or_gem_readl(bp, NCFGR);
	regs_buff[2]  = macb_readl(bp, NSR);
	regs_buff[3]  = macb_readl(bp, TSR);
	regs_buff[4]  = macb_readl(bp, RBQP);
	regs_buff[5]  = macb_readl(bp, TBQP);
	regs_buff[6]  = macb_readl(bp, RSR);
	regs_buff[7]  = macb_readl(bp, IMR);

	regs_buff[8]  = tail;
	regs_buff[9]  = head;
	regs_buff[10] = macb_tx_dma(&bp->queues[0], tail);
	regs_buff[11] = macb_tx_dma(&bp->queues[0], head);

	if (!(bp->caps & MACB_CAPS_USRIO_DISABLED))
		regs_buff[12] = macb_or_gem_readl(bp, USRIO);
	if (macb_is_gem(bp))
		regs_buff[13] = gem_readl(bp, DMACFG);
}