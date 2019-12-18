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
struct TYPE_2__ {int /*<<< orphan*/  txd_cnt; int /*<<< orphan*/  rxd_cnt; } ;
struct nfp_net {TYPE_1__ dp; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_MAX_RX_DESCS ; 
 int /*<<< orphan*/  NFP_NET_MAX_TX_DESCS ; 
 struct nfp_net* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void nfp_net_get_ringparam(struct net_device *netdev,
				  struct ethtool_ringparam *ring)
{
	struct nfp_net *nn = netdev_priv(netdev);

	ring->rx_max_pending = NFP_NET_MAX_RX_DESCS;
	ring->tx_max_pending = NFP_NET_MAX_TX_DESCS;
	ring->rx_pending = nn->dp.rxd_cnt;
	ring->tx_pending = nn->dp.txd_cnt;
}