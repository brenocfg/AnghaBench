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
typedef  int u32 ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int RXSR_MULTICAST ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 

__attribute__((used)) static void ks8842_update_rx_counters(struct net_device *netdev, u32 status,
	int len)
{
	netdev_dbg(netdev, "RX packet, len: %d\n", len);

	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += len;
	if (status & RXSR_MULTICAST)
		netdev->stats.multicast++;
}