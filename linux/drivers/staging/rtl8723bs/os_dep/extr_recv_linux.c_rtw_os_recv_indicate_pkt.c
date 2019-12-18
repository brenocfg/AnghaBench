#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct sta_priv {int dummy; } ;
struct sta_info {int dummy; } ;
struct rx_pkt_attrib {int tcpchk_valid; int tcp_chkrpt; int /*<<< orphan*/  dst; } ;
struct net_device {int dummy; } ;
struct mlme_priv {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  os_netif_err; int /*<<< orphan*/  os_netif_ok; int /*<<< orphan*/  os_indicate_ap_self; int /*<<< orphan*/  os_indicate_ap_forward; int /*<<< orphan*/  os_indicate_ap_mcast; } ;
struct adapter {TYPE_1__ rx_logs; struct net_device* pnetdev; int /*<<< orphan*/  eeprompriv; struct sta_priv stapriv; struct mlme_priv mlmepriv; } ;
struct TYPE_12__ {void* ip_summed; struct net_device* dev; int /*<<< orphan*/  protocol; } ;
typedef  TYPE_2__ _pkt ;

/* Variables and functions */
 void* CHECKSUM_NONE ; 
 void* CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DBG_COUNTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IS_MCAST (int /*<<< orphan*/ ) ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  _rtw_xmit_entry (TYPE_2__*,struct net_device*) ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (TYPE_2__*,struct net_device*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myid (int /*<<< orphan*/ *) ; 
 struct sta_info* rtw_get_bcmc_stainfo (struct adapter*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 
 int rtw_netif_rx (struct net_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  rtw_recv_select_queue (TYPE_2__*) ; 
 TYPE_2__* rtw_skb_clone (TYPE_2__*) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (TYPE_2__*,int /*<<< orphan*/ ) ; 

void rtw_os_recv_indicate_pkt(struct adapter *padapter, _pkt *pkt, struct rx_pkt_attrib *pattrib)
{
	struct mlme_priv*pmlmepriv = &padapter->mlmepriv;
	int ret;

	/* Indicat the packets to upper layer */
	if (pkt) {
		if (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true) {
			_pkt *pskb2 = NULL;
			struct sta_info *psta = NULL;
			struct sta_priv *pstapriv = &padapter->stapriv;
			int bmcast = IS_MCAST(pattrib->dst);

			/* DBG_871X("bmcast =%d\n", bmcast); */

			if (memcmp(pattrib->dst, myid(&padapter->eeprompriv), ETH_ALEN)) {
				/* DBG_871X("not ap psta =%p, addr =%pM\n", psta, pattrib->dst); */

				if (bmcast) {
					psta = rtw_get_bcmc_stainfo(padapter);
					pskb2 = rtw_skb_clone(pkt);
				} else {
					psta = rtw_get_stainfo(pstapriv, pattrib->dst);
				}

				if (psta) {
					struct net_device *pnetdev = (struct net_device*)padapter->pnetdev;

					/* DBG_871X("directly forwarding to the rtw_xmit_entry\n"); */

					/* skb->ip_summed = CHECKSUM_NONE; */
					pkt->dev = pnetdev;
					skb_set_queue_mapping(pkt, rtw_recv_select_queue(pkt));

					_rtw_xmit_entry(pkt, pnetdev);

					if (bmcast && (pskb2 != NULL)) {
						pkt = pskb2;
						DBG_COUNTER(padapter->rx_logs.os_indicate_ap_mcast);
					} else {
						DBG_COUNTER(padapter->rx_logs.os_indicate_ap_forward);
						return;
					}
				}
			} else {
				/*  to APself */
				/* DBG_871X("to APSelf\n"); */
				DBG_COUNTER(padapter->rx_logs.os_indicate_ap_self);
			}
		}

		pkt->protocol = eth_type_trans(pkt, padapter->pnetdev);
		pkt->dev = padapter->pnetdev;

#ifdef CONFIG_TCP_CSUM_OFFLOAD_RX
		if ((pattrib->tcpchk_valid == 1) && (pattrib->tcp_chkrpt == 1))
			pkt->ip_summed = CHECKSUM_UNNECESSARY;
		else
			pkt->ip_summed = CHECKSUM_NONE;

#else /* !CONFIG_TCP_CSUM_OFFLOAD_RX */
		pkt->ip_summed = CHECKSUM_NONE;
#endif /* CONFIG_TCP_CSUM_OFFLOAD_RX */

		ret = rtw_netif_rx(padapter->pnetdev, pkt);
		if (ret == NET_RX_SUCCESS)
			DBG_COUNTER(padapter->rx_logs.os_netif_ok);
		else
			DBG_COUNTER(padapter->rx_logs.os_netif_err);
	}
}