#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct fec_enet_private {int num_rx_queues; TYPE_2__** rx_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg_desc_active; } ;
struct TYPE_4__ {TYPE_1__ bd; } ;

/* Variables and functions */
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fec_enet_active_rxring(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int i;

	for (i = 0; i < fep->num_rx_queues; i++)
		writel(0, fep->rx_queue[i]->bd.reg_desc_active);
}