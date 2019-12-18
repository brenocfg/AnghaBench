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
struct dpaa_priv {int /*<<< orphan*/  percpu_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct dpaa_percpu_priv {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ dev_trans_start (struct net_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 struct dpaa_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_crit (struct dpaa_priv const*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct dpaa_percpu_priv* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void dpaa_tx_timeout(struct net_device *net_dev)
{
	struct dpaa_percpu_priv *percpu_priv;
	const struct dpaa_priv	*priv;

	priv = netdev_priv(net_dev);
	percpu_priv = this_cpu_ptr(priv->percpu_priv);

	netif_crit(priv, timer, net_dev, "Transmit timeout latency: %u ms\n",
		   jiffies_to_msecs(jiffies - dev_trans_start(net_dev)));

	percpu_priv->stats.tx_errors++;
}