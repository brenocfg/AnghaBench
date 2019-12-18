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
struct net_device {int real_num_tx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_stop_subqueue (struct net_device*,int) ; 

__attribute__((used)) static inline void stop_txqs(struct net_device *netdev)
{
	int i;

	for (i = 0; i < netdev->real_num_tx_queues; i++)
		netif_stop_subqueue(netdev, i);
}