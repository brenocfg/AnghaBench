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
struct netdata_local {int /*<<< orphan*/  lock; int /*<<< orphan*/  napi; int /*<<< orphan*/  net_base; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  LPC_ENET_INTCLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_INTSTATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc_eth_disable_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct netdata_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t __lpc_eth_interrupt(int irq, void *dev_id)
{
	struct net_device *ndev = dev_id;
	struct netdata_local *pldat = netdev_priv(ndev);
	u32 tmp;

	spin_lock(&pldat->lock);

	tmp = readl(LPC_ENET_INTSTATUS(pldat->net_base));
	/* Clear interrupts */
	writel(tmp, LPC_ENET_INTCLEAR(pldat->net_base));

	lpc_eth_disable_int(pldat->net_base);
	if (likely(napi_schedule_prep(&pldat->napi)))
		__napi_schedule(&pldat->napi);

	spin_unlock(&pldat->lock);

	return IRQ_HANDLED;
}