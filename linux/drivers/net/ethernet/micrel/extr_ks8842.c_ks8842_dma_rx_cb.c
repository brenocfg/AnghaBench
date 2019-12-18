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
struct TYPE_2__ {int /*<<< orphan*/  tasklet; scalar_t__ adesc; } ;
struct ks8842_adapter {TYPE_1__ dma_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct ks8842_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ks8842_dma_rx_cb(void *data)
{
	struct net_device	*netdev = data;
	struct ks8842_adapter	*adapter = netdev_priv(netdev);

	netdev_dbg(netdev, "RX DMA finished\n");
	/* schedule tasklet */
	if (adapter->dma_rx.adesc)
		tasklet_schedule(&adapter->dma_rx.tasklet);
}