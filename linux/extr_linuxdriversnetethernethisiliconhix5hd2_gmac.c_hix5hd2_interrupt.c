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
struct hix5hd2_priv {int /*<<< orphan*/  napi; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DEF_INT_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ RAW_PMU_INT ; 
 int /*<<< orphan*/  hix5hd2_irq_disable (struct hix5hd2_priv*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct hix5hd2_priv* netdev_priv (struct net_device*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t hix5hd2_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct hix5hd2_priv *priv = netdev_priv(dev);
	int ints = readl_relaxed(priv->base + RAW_PMU_INT);

	writel_relaxed(ints, priv->base + RAW_PMU_INT);
	if (likely(ints & DEF_INT_MASK)) {
		hix5hd2_irq_disable(priv);
		napi_schedule(&priv->napi);
	}

	return IRQ_HANDLED;
}