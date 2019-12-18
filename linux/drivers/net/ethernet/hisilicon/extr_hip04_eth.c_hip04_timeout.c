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
struct hip04_priv {int /*<<< orphan*/  tx_timeout_task; } ;

/* Variables and functions */
 struct hip04_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hip04_timeout(struct net_device *ndev)
{
	struct hip04_priv *priv = netdev_priv(ndev);

	schedule_work(&priv->tx_timeout_task);
}