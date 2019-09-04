#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rxerr; int /*<<< orphan*/  txerr; } ;
struct peak_canfd_priv {TYPE_1__ bec; TYPE_2__* ndev; } ;
struct net_device_stats {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_over_errors; } ;
struct can_frame {scalar_t__ can_dlc; int /*<<< orphan*/ * data; int /*<<< orphan*/  can_id; } ;
struct TYPE_4__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_ERR_CRTL ; 
 int /*<<< orphan*/  CAN_ERR_CRTL_RX_OVERFLOW ; 
 int ENOMEM ; 
 struct sk_buff* alloc_can_err_skb (TYPE_2__*,struct can_frame**) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

__attribute__((used)) static int pucan_handle_cache_critical(struct peak_canfd_priv *priv)
{
	struct net_device_stats *stats = &priv->ndev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;

	stats->rx_over_errors++;
	stats->rx_errors++;

	skb = alloc_can_err_skb(priv->ndev, &cf);
	if (!skb) {
		stats->rx_dropped++;
		return -ENOMEM;
	}

	cf->can_id |= CAN_ERR_CRTL;
	cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;

	cf->data[6] = priv->bec.txerr;
	cf->data[7] = priv->bec.rxerr;

	stats->rx_bytes += cf->can_dlc;
	stats->rx_packets++;
	netif_rx(skb);

	return 0;
}