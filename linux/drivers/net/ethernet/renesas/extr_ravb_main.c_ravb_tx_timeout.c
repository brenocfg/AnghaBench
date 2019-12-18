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
struct ravb_private {int /*<<< orphan*/  work; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISS ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ravb_private*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_read (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_err ; 

__attribute__((used)) static void ravb_tx_timeout(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);

	netif_err(priv, tx_err, ndev,
		  "transmit timed out, status %08x, resetting...\n",
		  ravb_read(ndev, ISS));

	/* tx_errors count up */
	ndev->stats.tx_errors++;

	schedule_work(&priv->work);
}