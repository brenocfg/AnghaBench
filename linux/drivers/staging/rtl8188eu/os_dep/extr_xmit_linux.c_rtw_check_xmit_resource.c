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
typedef  size_t u16 ;
struct xmit_priv {int free_xmitframe_cnt; TYPE_2__* hwxmits; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {scalar_t__ wifi_spec; } ;
struct adapter {int /*<<< orphan*/  pnetdev; TYPE_1__ registrypriv; struct xmit_priv xmitpriv; } ;
struct TYPE_4__ {scalar_t__ accnt; } ;

/* Variables and functions */
 scalar_t__ WMM_XMIT_THRESHOLD ; 
 int /*<<< orphan*/  netdev_get_tx_queue (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  netif_stop_subqueue (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  netif_tx_queue_stopped (int /*<<< orphan*/ ) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 

__attribute__((used)) static void rtw_check_xmit_resource(struct adapter *padapter,
				    struct sk_buff *pkt)
{
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	u16 queue;

	queue = skb_get_queue_mapping(pkt);
	if (padapter->registrypriv.wifi_spec) {
		/* No free space for Tx, tx_worker is too slow */
		if (pxmitpriv->hwxmits[queue].accnt > WMM_XMIT_THRESHOLD)
			netif_stop_subqueue(padapter->pnetdev, queue);
	} else {
		if (pxmitpriv->free_xmitframe_cnt <= 4) {
			if (!netif_tx_queue_stopped(netdev_get_tx_queue(padapter->pnetdev, queue)))
				netif_stop_subqueue(padapter->pnetdev, queue);
		}
	}
}