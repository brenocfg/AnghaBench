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
struct r8152 {int rx_pending; int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int rx_pending; } ;

/* Variables and functions */
 int EINVAL ; 
 int RTL8152_MAX_RX ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int rtl8152_set_ringparam(struct net_device *netdev,
				 struct ethtool_ringparam *ring)
{
	struct r8152 *tp = netdev_priv(netdev);

	if (ring->rx_pending < (RTL8152_MAX_RX * 2))
		return -EINVAL;

	if (tp->rx_pending != ring->rx_pending) {
		napi_disable(&tp->napi);
		tp->rx_pending = ring->rx_pending;
		napi_enable(&tp->napi);
	}

	return 0;
}