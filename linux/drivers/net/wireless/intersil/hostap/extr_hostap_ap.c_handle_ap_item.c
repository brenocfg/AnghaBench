#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct ieee80211_hdr {int addr1; int addr3; int /*<<< orphan*/  frame_control; } ;
struct hostap_80211_rx_status {int dummy; } ;
struct TYPE_13__ {scalar_t__ hostapd; TYPE_1__* ap; struct net_device* dev; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_12__ {scalar_t__ nullfunc_ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_AP ; 
 int IEEE80211_FCTL_FROMDS ; 
 int IEEE80211_FCTL_FTYPE ; 
 int IEEE80211_FCTL_STYPE ; 
 int IEEE80211_FCTL_TODS ; 
 int IEEE80211_FTYPE_CTL ; 
 int IEEE80211_FTYPE_DATA ; 
 int IEEE80211_FTYPE_MGMT ; 
#define  IEEE80211_STYPE_ASSOC_REQ 135 
#define  IEEE80211_STYPE_ASSOC_RESP 134 
#define  IEEE80211_STYPE_ATIM 133 
#define  IEEE80211_STYPE_AUTH 132 
 int IEEE80211_STYPE_BEACON ; 
#define  IEEE80211_STYPE_DEAUTH 131 
#define  IEEE80211_STYPE_DISASSOC 130 
 int IEEE80211_STYPE_NULLFUNC ; 
 int IEEE80211_STYPE_PSPOLL ; 
#define  IEEE80211_STYPE_REASSOC_REQ 129 
#define  IEEE80211_STYPE_REASSOC_RESP 128 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ap_handle_data_nullfunc (TYPE_2__*,struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  ap_handle_dropped_data (TYPE_2__*,struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_equal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_assoc (TYPE_2__*,struct sk_buff*,struct hostap_80211_rx_status*,int) ; 
 int /*<<< orphan*/  handle_authen (TYPE_2__*,struct sk_buff*,struct hostap_80211_rx_status*) ; 
 int /*<<< orphan*/  handle_beacon (TYPE_2__*,struct sk_buff*,struct hostap_80211_rx_status*) ; 
 int /*<<< orphan*/  handle_deauth (TYPE_2__*,struct sk_buff*,struct hostap_80211_rx_status*) ; 
 int /*<<< orphan*/  handle_disassoc (TYPE_2__*,struct sk_buff*,struct hostap_80211_rx_status*) ; 
 int /*<<< orphan*/  handle_pspoll (TYPE_2__*,struct ieee80211_hdr*,struct hostap_80211_rx_status*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_ap_item(local_info_t *local, struct sk_buff *skb,
			   struct hostap_80211_rx_status *rx_stats)
{
#ifndef PRISM2_NO_KERNEL_IEEE80211_MGMT
	struct net_device *dev = local->dev;
#endif /* PRISM2_NO_KERNEL_IEEE80211_MGMT */
	u16 fc, type, stype;
	struct ieee80211_hdr *hdr;

	/* FIX: should give skb->len to handler functions and check that the
	 * buffer is long enough */
	hdr = (struct ieee80211_hdr *) skb->data;
	fc = le16_to_cpu(hdr->frame_control);
	type = fc & IEEE80211_FCTL_FTYPE;
	stype = fc & IEEE80211_FCTL_STYPE;

#ifndef PRISM2_NO_KERNEL_IEEE80211_MGMT
	if (!local->hostapd && type == IEEE80211_FTYPE_DATA) {
		PDEBUG(DEBUG_AP, "handle_ap_item - data frame\n");

		if (!(fc & IEEE80211_FCTL_TODS) ||
		    (fc & IEEE80211_FCTL_FROMDS)) {
			if (stype == IEEE80211_STYPE_NULLFUNC) {
				/* no ToDS nullfunc seems to be used to check
				 * AP association; so send reject message to
				 * speed up re-association */
				ap_handle_dropped_data(local, hdr);
				goto done;
			}
			PDEBUG(DEBUG_AP, "   not ToDS frame (fc=0x%04x)\n",
			       fc);
			goto done;
		}

		if (!ether_addr_equal(hdr->addr1, dev->dev_addr)) {
			PDEBUG(DEBUG_AP, "handle_ap_item - addr1(BSSID)=%pM"
			       " not own MAC\n", hdr->addr1);
			goto done;
		}

		if (local->ap->nullfunc_ack &&
		    stype == IEEE80211_STYPE_NULLFUNC)
			ap_handle_data_nullfunc(local, hdr);
		else
			ap_handle_dropped_data(local, hdr);
		goto done;
	}

	if (type == IEEE80211_FTYPE_MGMT && stype == IEEE80211_STYPE_BEACON) {
		handle_beacon(local, skb, rx_stats);
		goto done;
	}
#endif /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

	if (type == IEEE80211_FTYPE_CTL && stype == IEEE80211_STYPE_PSPOLL) {
		handle_pspoll(local, hdr, rx_stats);
		goto done;
	}

	if (local->hostapd) {
		PDEBUG(DEBUG_AP, "Unknown frame in AP queue: type=0x%02x "
		       "subtype=0x%02x\n", type, stype);
		goto done;
	}

#ifndef PRISM2_NO_KERNEL_IEEE80211_MGMT
	if (type != IEEE80211_FTYPE_MGMT) {
		PDEBUG(DEBUG_AP, "handle_ap_item - not a management frame?\n");
		goto done;
	}

	if (!ether_addr_equal(hdr->addr1, dev->dev_addr)) {
		PDEBUG(DEBUG_AP, "handle_ap_item - addr1(DA)=%pM"
		       " not own MAC\n", hdr->addr1);
		goto done;
	}

	if (!ether_addr_equal(hdr->addr3, dev->dev_addr)) {
		PDEBUG(DEBUG_AP, "handle_ap_item - addr3(BSSID)=%pM"
		       " not own MAC\n", hdr->addr3);
		goto done;
	}

	switch (stype) {
	case IEEE80211_STYPE_ASSOC_REQ:
		handle_assoc(local, skb, rx_stats, 0);
		break;
	case IEEE80211_STYPE_ASSOC_RESP:
		PDEBUG(DEBUG_AP, "==> ASSOC RESP (ignored)\n");
		break;
	case IEEE80211_STYPE_REASSOC_REQ:
		handle_assoc(local, skb, rx_stats, 1);
		break;
	case IEEE80211_STYPE_REASSOC_RESP:
		PDEBUG(DEBUG_AP, "==> REASSOC RESP (ignored)\n");
		break;
	case IEEE80211_STYPE_ATIM:
		PDEBUG(DEBUG_AP, "==> ATIM (ignored)\n");
		break;
	case IEEE80211_STYPE_DISASSOC:
		handle_disassoc(local, skb, rx_stats);
		break;
	case IEEE80211_STYPE_AUTH:
		handle_authen(local, skb, rx_stats);
		break;
	case IEEE80211_STYPE_DEAUTH:
		handle_deauth(local, skb, rx_stats);
		break;
	default:
		PDEBUG(DEBUG_AP, "Unknown mgmt frame subtype 0x%02x\n",
		       stype >> 4);
		break;
	}
#endif /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

 done:
	dev_kfree_skb(skb);
}