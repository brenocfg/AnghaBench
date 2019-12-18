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
struct ltq_etop_priv {int /*<<< orphan*/ * ch; } ;

/* Variables and functions */
 scalar_t__ IS_RX (int) ; 
 scalar_t__ IS_TX (int) ; 
 int MAX_DMA_CHAN ; 
 int /*<<< orphan*/  PMU_PPE ; 
 int /*<<< orphan*/  ltq_etop_free_channel (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ltq_pmu_disable (int /*<<< orphan*/ ) ; 
 struct ltq_etop_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
ltq_etop_hw_exit(struct net_device *dev)
{
	struct ltq_etop_priv *priv = netdev_priv(dev);
	int i;

	ltq_pmu_disable(PMU_PPE);
	for (i = 0; i < MAX_DMA_CHAN; i++)
		if (IS_TX(i) || IS_RX(i))
			ltq_etop_free_channel(dev, &priv->ch[i]);
}