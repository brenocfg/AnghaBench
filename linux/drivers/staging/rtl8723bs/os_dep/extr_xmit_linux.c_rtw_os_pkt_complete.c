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
struct xmit_priv {TYPE_2__* hwxmits; } ;
struct TYPE_3__ {scalar_t__ wifi_spec; } ;
struct adapter {int /*<<< orphan*/  pnetdev; TYPE_1__ registrypriv; struct xmit_priv xmitpriv; } ;
typedef  int /*<<< orphan*/  _pkt ;
struct TYPE_4__ {scalar_t__ accnt; } ;

/* Variables and functions */
 scalar_t__ WMM_XMIT_THRESHOLD ; 
 scalar_t__ __netif_subqueue_stopped (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_subqueue (int /*<<< orphan*/ ,size_t) ; 
 size_t skb_get_queue_mapping (int /*<<< orphan*/ *) ; 

void rtw_os_pkt_complete(struct adapter *padapter, _pkt *pkt)
{
	u16 queue;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;

	queue = skb_get_queue_mapping(pkt);
	if (padapter->registrypriv.wifi_spec) {
		if (__netif_subqueue_stopped(padapter->pnetdev, queue) &&
		    (pxmitpriv->hwxmits[queue].accnt < WMM_XMIT_THRESHOLD))
			netif_wake_subqueue(padapter->pnetdev, queue);
	} else {
		if (__netif_subqueue_stopped(padapter->pnetdev, queue))
			netif_wake_subqueue(padapter->pnetdev, queue);
	}

	dev_kfree_skb_any(pkt);
}