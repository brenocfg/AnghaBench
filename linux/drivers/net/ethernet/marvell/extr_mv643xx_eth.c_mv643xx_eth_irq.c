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
struct net_device {int dummy; } ;
struct mv643xx_eth_private {int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  mv643xx_eth_collect_events (struct mv643xx_eth_private*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mv643xx_eth_irq(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct mv643xx_eth_private *mp = netdev_priv(dev);

	if (unlikely(!mv643xx_eth_collect_events(mp)))
		return IRQ_NONE;

	wrlp(mp, INT_MASK, 0);
	napi_schedule(&mp->napi);

	return IRQ_HANDLED;
}