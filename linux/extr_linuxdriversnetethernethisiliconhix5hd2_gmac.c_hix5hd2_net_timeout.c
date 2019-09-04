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
struct hix5hd2_priv {int /*<<< orphan*/  tx_timeout_task; } ;

/* Variables and functions */
 struct hix5hd2_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hix5hd2_net_timeout(struct net_device *dev)
{
	struct hix5hd2_priv *priv = netdev_priv(dev);

	schedule_work(&priv->tx_timeout_task);
}