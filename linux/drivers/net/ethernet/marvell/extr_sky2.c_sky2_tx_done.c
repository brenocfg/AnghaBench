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
typedef  int /*<<< orphan*/  u16 ;
struct sky2_port {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_SKB_TX_LE ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  sky2_tx_complete (struct sky2_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ tx_avail (struct sky2_port*) ; 

__attribute__((used)) static inline void sky2_tx_done(struct net_device *dev, u16 last)
{
	struct sky2_port *sky2 = netdev_priv(dev);

	if (netif_running(dev)) {
		sky2_tx_complete(sky2, last);

		/* Wake unless it's detached, and called e.g. from sky2_close() */
		if (tx_avail(sky2) > MAX_SKB_TX_LE + 4)
			netif_wake_queue(dev);
	}
}