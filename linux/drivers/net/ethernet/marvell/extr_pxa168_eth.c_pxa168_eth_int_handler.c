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
struct pxa168_eth_private {int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct pxa168_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pxa168_eth_collect_events (struct pxa168_eth_private*,struct net_device*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wrl (struct pxa168_eth_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t pxa168_eth_int_handler(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct pxa168_eth_private *pep = netdev_priv(dev);

	if (unlikely(!pxa168_eth_collect_events(pep, dev)))
		return IRQ_NONE;
	/* Disable interrupts */
	wrl(pep, INT_MASK, 0);
	napi_schedule(&pep->napi);
	return IRQ_HANDLED;
}