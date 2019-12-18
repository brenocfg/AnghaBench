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
typedef  int u8 ;
struct TYPE_4__ {scalar_t__ iftype; } ;
struct wil6210_vif {TYPE_2__ wdev; } ;
struct wil6210_priv {int max_assoc_sta; TYPE_1__* sta; struct wil6210_vif** vifs; } ;
struct vring_rx_desc {int dummy; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct ieee80211_hdr_3addr {unsigned char* addr2; } ;
struct TYPE_3__ {scalar_t__ status; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ ETH_HLEN ; 
 int IEEE80211_FTYPE_DATA ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 scalar_t__ NL80211_IFTYPE_P2P_GO ; 
 int WIL6210_RX_DESC_MAX_CID ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wil_err_ratelimited (struct wil6210_priv*,char*,...) ; 
 unsigned int wil_rx_snaplen () ; 
 int wil_rxdesc_cid (struct vring_rx_desc*) ; 
 int wil_rxdesc_ftype (struct vring_rx_desc*) ; 
 int wil_rxdesc_mid (struct vring_rx_desc*) ; 
 unsigned char* wil_skb_get_sa (struct sk_buff*) ; 
 struct vring_rx_desc* wil_skb_rxdesc (struct sk_buff*) ; 
 scalar_t__ wil_sta_unused ; 

__attribute__((used)) static int wil_rx_get_cid_by_skb(struct wil6210_priv *wil, struct sk_buff *skb)
{
	struct vring_rx_desc *d = wil_skb_rxdesc(skb);
	int mid = wil_rxdesc_mid(d);
	struct wil6210_vif *vif = wil->vifs[mid];
	/* cid from DMA descriptor is limited to 3 bits.
	 * In case of cid>=8, the value would be cid modulo 8 and we need to
	 * find real cid by locating the transmitter (ta) inside sta array
	 */
	int cid = wil_rxdesc_cid(d);
	unsigned int snaplen = wil_rx_snaplen();
	struct ieee80211_hdr_3addr *hdr;
	int i;
	unsigned char *ta;
	u8 ftype;

	/* in monitor mode there are no connections */
	if (vif->wdev.iftype == NL80211_IFTYPE_MONITOR)
		return cid;

	ftype = wil_rxdesc_ftype(d) << 2;
	if (likely(ftype == IEEE80211_FTYPE_DATA)) {
		if (unlikely(skb->len < ETH_HLEN + snaplen)) {
			wil_err_ratelimited(wil,
					    "Short data frame, len = %d\n",
					    skb->len);
			return -ENOENT;
		}
		ta = wil_skb_get_sa(skb);
	} else {
		if (unlikely(skb->len < sizeof(struct ieee80211_hdr_3addr))) {
			wil_err_ratelimited(wil, "Short frame, len = %d\n",
					    skb->len);
			return -ENOENT;
		}
		hdr = (void *)skb->data;
		ta = hdr->addr2;
	}

	if (wil->max_assoc_sta <= WIL6210_RX_DESC_MAX_CID)
		return cid;

	/* assuming no concurrency between AP interfaces and STA interfaces.
	 * multista is used only in P2P_GO or AP mode. In other modes return
	 * cid from the rx descriptor
	 */
	if (vif->wdev.iftype != NL80211_IFTYPE_P2P_GO &&
	    vif->wdev.iftype != NL80211_IFTYPE_AP)
		return cid;

	/* For Rx packets cid from rx descriptor is limited to 3 bits (0..7),
	 * to find the real cid, compare transmitter address with the stored
	 * stations mac address in the driver sta array
	 */
	for (i = cid; i < wil->max_assoc_sta; i += WIL6210_RX_DESC_MAX_CID) {
		if (wil->sta[i].status != wil_sta_unused &&
		    ether_addr_equal(wil->sta[i].addr, ta)) {
			cid = i;
			break;
		}
	}
	if (i >= wil->max_assoc_sta) {
		wil_err_ratelimited(wil, "Could not find cid for frame with transmit addr = %pM, iftype = %d, frametype = %d, len = %d\n",
				    ta, vif->wdev.iftype, ftype, skb->len);
		cid = -ENOENT;
	}

	return cid;
}