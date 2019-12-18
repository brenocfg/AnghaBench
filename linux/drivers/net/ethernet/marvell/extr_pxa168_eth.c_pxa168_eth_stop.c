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
struct pxa168_eth_private {int /*<<< orphan*/  timeout; int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_CAUSE ; 
 int /*<<< orphan*/  INT_MASK ; 
 int /*<<< orphan*/  INT_W_CLEAR ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_port_reset (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct pxa168_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  rxq_deinit (struct net_device*) ; 
 int /*<<< orphan*/  txq_deinit (struct net_device*) ; 
 int /*<<< orphan*/  wrl (struct pxa168_eth_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa168_eth_stop(struct net_device *dev)
{
	struct pxa168_eth_private *pep = netdev_priv(dev);
	eth_port_reset(dev);

	/* Disable interrupts */
	wrl(pep, INT_MASK, 0);
	wrl(pep, INT_CAUSE, 0);
	/* Write to ICR to clear interrupts. */
	wrl(pep, INT_W_CLEAR, 0);
	napi_disable(&pep->napi);
	del_timer_sync(&pep->timeout);
	netif_carrier_off(dev);
	free_irq(dev->irq, dev);
	rxq_deinit(dev);
	txq_deinit(dev);

	return 0;
}