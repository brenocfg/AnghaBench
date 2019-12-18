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
struct net_device {int dummy; } ;
struct ipw_priv {struct clx2_tx_queue* txq; } ;
struct TYPE_2__ {scalar_t__ high_mark; } ;
struct clx2_tx_queue {TYPE_1__ q; } ;

/* Variables and functions */
 int ipw_get_tx_queue_number (struct ipw_priv*,int) ; 
 scalar_t__ ipw_tx_queue_space (TYPE_1__*) ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 

__attribute__((used)) static int ipw_net_is_queue_full(struct net_device *dev, int pri)
{
	struct ipw_priv *priv = libipw_priv(dev);
#ifdef CONFIG_IPW2200_QOS
	int tx_id = ipw_get_tx_queue_number(priv, pri);
	struct clx2_tx_queue *txq = &priv->txq[tx_id];
#else
	struct clx2_tx_queue *txq = &priv->txq[0];
#endif				/* CONFIG_IPW2200_QOS */

	if (ipw_tx_queue_space(&txq->q) < txq->q.high_mark)
		return 1;

	return 0;
}