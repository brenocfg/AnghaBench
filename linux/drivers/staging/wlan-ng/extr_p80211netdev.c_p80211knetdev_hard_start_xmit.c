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
union p80211_hdr {int /*<<< orphan*/ * data; } ;
struct wlandevice {scalar_t__ state; int macmode; int (* txframe ) (struct wlandevice*,struct sk_buff*,union p80211_hdr*,union p80211_hdr*) ;int /*<<< orphan*/  netdev; int /*<<< orphan*/  ethconv; } ;
struct sk_buff {int /*<<< orphan*/ * data; scalar_t__ len; int /*<<< orphan*/  protocol; } ;
struct p80211_metawep {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; struct wlandevice* ml_priv; } ;
typedef  int /*<<< orphan*/  p80211_wep ;
typedef  int /*<<< orphan*/  p80211_hdr ;
typedef  int netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 scalar_t__ ETH_P_80211_RAW ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 scalar_t__ WLAN_DEVICE_OPEN ; 
#define  WLAN_MACMODE_ESS_AP 130 
#define  WLAN_MACMODE_ESS_STA 129 
#define  WLAN_MACMODE_IBSS_STA 128 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (union p80211_hdr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (union p80211_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_ether_to_p80211 (struct wlandevice*,int /*<<< orphan*/ ,struct sk_buff*,union p80211_hdr*,union p80211_hdr*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int stub1 (struct wlandevice*,struct sk_buff*,union p80211_hdr*,union p80211_hdr*) ; 

__attribute__((used)) static netdev_tx_t p80211knetdev_hard_start_xmit(struct sk_buff *skb,
						 struct net_device *netdev)
{
	int result = 0;
	int txresult = -1;
	struct wlandevice *wlandev = netdev->ml_priv;
	union p80211_hdr p80211_hdr;
	struct p80211_metawep p80211_wep;

	p80211_wep.data = NULL;

	if (!skb)
		return NETDEV_TX_OK;

	if (wlandev->state != WLAN_DEVICE_OPEN) {
		result = 1;
		goto failed;
	}

	memset(&p80211_hdr, 0, sizeof(p80211_hdr));
	memset(&p80211_wep, 0, sizeof(p80211_wep));

	if (netif_queue_stopped(netdev)) {
		netdev_dbg(netdev, "called when queue stopped.\n");
		result = 1;
		goto failed;
	}

	netif_stop_queue(netdev);

	/* Check to see that a valid mode is set */
	switch (wlandev->macmode) {
	case WLAN_MACMODE_IBSS_STA:
	case WLAN_MACMODE_ESS_STA:
	case WLAN_MACMODE_ESS_AP:
		break;
	default:
		/* Mode isn't set yet, just drop the frame
		 * and return success .
		 * TODO: we need a saner way to handle this
		 */
		if (be16_to_cpu(skb->protocol) != ETH_P_80211_RAW) {
			netif_start_queue(wlandev->netdev);
			netdev_notice(netdev, "Tx attempt prior to association, frame dropped.\n");
			netdev->stats.tx_dropped++;
			result = 0;
			goto failed;
		}
		break;
	}

	/* Check for raw transmits */
	if (be16_to_cpu(skb->protocol) == ETH_P_80211_RAW) {
		if (!capable(CAP_NET_ADMIN)) {
			result = 1;
			goto failed;
		}
		/* move the header over */
		memcpy(&p80211_hdr, skb->data, sizeof(p80211_hdr));
		skb_pull(skb, sizeof(p80211_hdr));
	} else {
		if (skb_ether_to_p80211
		    (wlandev, wlandev->ethconv, skb, &p80211_hdr,
		     &p80211_wep) != 0) {
			/* convert failed */
			netdev_dbg(netdev, "ether_to_80211(%d) failed.\n",
				   wlandev->ethconv);
			result = 1;
			goto failed;
		}
	}
	if (!wlandev->txframe) {
		result = 1;
		goto failed;
	}

	netif_trans_update(netdev);

	netdev->stats.tx_packets++;
	/* count only the packet payload */
	netdev->stats.tx_bytes += skb->len;

	txresult = wlandev->txframe(wlandev, skb, &p80211_hdr, &p80211_wep);

	if (txresult == 0) {
		/* success and more buf */
		/* avail, re: hw_txdata */
		netif_wake_queue(wlandev->netdev);
		result = NETDEV_TX_OK;
	} else if (txresult == 1) {
		/* success, no more avail */
		netdev_dbg(netdev, "txframe success, no more bufs\n");
		/* netdev->tbusy = 1;  don't set here, irqhdlr */
		/*   may have already cleared it */
		result = NETDEV_TX_OK;
	} else if (txresult == 2) {
		/* alloc failure, drop frame */
		netdev_dbg(netdev, "txframe returned alloc_fail\n");
		result = NETDEV_TX_BUSY;
	} else {
		/* buffer full or queue busy, drop frame. */
		netdev_dbg(netdev, "txframe returned full or busy\n");
		result = NETDEV_TX_BUSY;
	}

failed:
	/* Free up the WEP buffer if it's not the same as the skb */
	if ((p80211_wep.data) && (p80211_wep.data != skb->data))
		kzfree(p80211_wep.data);

	/* we always free the skb here, never in a lower level. */
	if (!result)
		dev_kfree_skb(skb);

	return result;
}