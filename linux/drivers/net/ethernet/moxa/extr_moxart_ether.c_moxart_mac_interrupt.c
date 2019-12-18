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
struct moxart_mac_priv_t {int /*<<< orphan*/  napi; scalar_t__ base; int /*<<< orphan*/  reg_imr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ REG_INTERRUPT_MASK ; 
 scalar_t__ REG_INTERRUPT_STATUS ; 
 unsigned int RPKT_FINISH ; 
 int /*<<< orphan*/  RPKT_FINISH_M ; 
 unsigned int XPKT_OK_INT_STS ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  moxart_tx_finished (struct net_device*) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct moxart_mac_priv_t* netdev_priv (struct net_device*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t moxart_mac_interrupt(int irq, void *dev_id)
{
	struct net_device *ndev = (struct net_device *)dev_id;
	struct moxart_mac_priv_t *priv = netdev_priv(ndev);
	unsigned int ists = readl(priv->base + REG_INTERRUPT_STATUS);

	if (ists & XPKT_OK_INT_STS)
		moxart_tx_finished(ndev);

	if (ists & RPKT_FINISH) {
		if (napi_schedule_prep(&priv->napi)) {
			priv->reg_imr &= ~RPKT_FINISH_M;
			writel(priv->reg_imr, priv->base + REG_INTERRUPT_MASK);
			__napi_schedule(&priv->napi);
		}
	}

	return IRQ_HANDLED;
}