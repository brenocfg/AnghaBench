#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtllib_device {TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  trans_start; } ;
struct TYPE_4__ {unsigned int num_tx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 TYPE_2__* netdev_get_tx_queue (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (TYPE_1__*) ; 

void rtllib_stop_all_queues(struct rtllib_device *ieee)
{
	unsigned int i;

	for (i = 0; i < ieee->dev->num_tx_queues; i++)
		netdev_get_tx_queue(ieee->dev, i)->trans_start = jiffies;

	netif_tx_stop_all_queues(ieee->dev);
}