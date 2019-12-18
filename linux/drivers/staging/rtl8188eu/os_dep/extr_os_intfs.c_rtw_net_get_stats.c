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
struct xmit_priv {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_drop; int /*<<< orphan*/  tx_pkts; } ;
struct recv_priv {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_drop; int /*<<< orphan*/  rx_pkts; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int dummy; } ;
struct adapter {struct net_device_stats stats; struct recv_priv recvpriv; struct xmit_priv xmitpriv; } ;

/* Variables and functions */
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *rtw_net_get_stats(struct net_device *pnetdev)
{
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(pnetdev);
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct recv_priv *precvpriv = &padapter->recvpriv;

	padapter->stats.tx_packets = pxmitpriv->tx_pkts;
	padapter->stats.rx_packets = precvpriv->rx_pkts;
	padapter->stats.tx_dropped = pxmitpriv->tx_drop;
	padapter->stats.rx_dropped = precvpriv->rx_drop;
	padapter->stats.tx_bytes = pxmitpriv->tx_bytes;
	padapter->stats.rx_bytes = precvpriv->rx_bytes;
	return &padapter->stats;
}