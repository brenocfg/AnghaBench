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
struct hisi_femac_priv {int /*<<< orphan*/  napi; scalar_t__ glb_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DEF_INT_MASK ; 
 scalar_t__ GLB_IRQ_RAW ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  hisi_femac_irq_disable (struct hisi_femac_priv*,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct hisi_femac_priv* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t hisi_femac_interrupt(int irq, void *dev_id)
{
	int ints;
	struct net_device *dev = (struct net_device *)dev_id;
	struct hisi_femac_priv *priv = netdev_priv(dev);

	ints = readl(priv->glb_base + GLB_IRQ_RAW);

	if (likely(ints & DEF_INT_MASK)) {
		writel(ints & DEF_INT_MASK,
		       priv->glb_base + GLB_IRQ_RAW);
		hisi_femac_irq_disable(priv, DEF_INT_MASK);
		napi_schedule(&priv->napi);
	}

	return IRQ_HANDLED;
}