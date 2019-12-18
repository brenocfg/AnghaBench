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
struct r8152 {int /*<<< orphan*/  rx_pending; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8152_RX_MAX_PENDING ; 
 struct r8152* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void rtl8152_get_ringparam(struct net_device *netdev,
				  struct ethtool_ringparam *ring)
{
	struct r8152 *tp = netdev_priv(netdev);

	ring->rx_max_pending = RTL8152_RX_MAX_PENDING;
	ring->rx_pending = tp->rx_pending;
}