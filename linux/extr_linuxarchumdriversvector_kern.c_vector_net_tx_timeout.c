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
struct TYPE_2__ {int /*<<< orphan*/  tx_timeout_count; } ;
struct vector_private {int /*<<< orphan*/  reset_tx; TYPE_1__ estats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct vector_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vector_net_tx_timeout(struct net_device *dev)
{
	struct vector_private *vp = netdev_priv(dev);

	vp->estats.tx_timeout_count++;
	netif_trans_update(dev);
	schedule_work(&vp->reset_tx);
}