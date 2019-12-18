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
struct xenvif_queue {unsigned int id; TYPE_1__* vif; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_get_tx_queue (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (int /*<<< orphan*/ ) ; 

void xenvif_wake_queue(struct xenvif_queue *queue)
{
	struct net_device *dev = queue->vif->dev;
	unsigned int id = queue->id;
	netif_tx_wake_queue(netdev_get_tx_queue(dev, id));
}