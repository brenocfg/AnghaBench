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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct encx24j600_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ dev_trans_start (struct net_device*) ; 
 scalar_t__ jiffies ; 
 struct encx24j600_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct encx24j600_priv*,int /*<<< orphan*/ ,struct net_device*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  tx_err ; 

__attribute__((used)) static void encx24j600_tx_timeout(struct net_device *dev)
{
	struct encx24j600_priv *priv = netdev_priv(dev);

	netif_err(priv, tx_err, dev, "TX timeout at %ld, latency %ld\n",
		  jiffies, jiffies - dev_trans_start(dev));

	dev->stats.tx_errors++;
	netif_wake_queue(dev);
}