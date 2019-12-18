#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ seq; scalar_t__ dur; int /*<<< orphan*/  fc; struct wlan_ethhdr* a3; struct wlan_ethhdr* a2; struct wlan_ethhdr* a1; } ;
union p80211_hdr {TYPE_1__ a3; } ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct wlandevice {int macmode; int hostwep; TYPE_2__* netdev; int /*<<< orphan*/ * bssid; } ;
struct wlan_snap {struct wlan_ethhdr* oui; int /*<<< orphan*/  type; } ;
struct wlan_llc {int dsap; int ssap; int ctl; } ;
struct wlan_ethhdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  type; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct p80211_metawep {int /*<<< orphan*/ * data; int /*<<< orphan*/  icv; int /*<<< orphan*/  iv; } ;
typedef  int /*<<< orphan*/  e_hdr ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_5__ {int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETH_ALEN ; 
 scalar_t__ ETH_DATA_LEN ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HOSTWEP_DEFAULTKEY_MASK ; 
 int HOSTWEP_ENCRYPT ; 
 int HOSTWEP_PRIVACYINVOKED ; 
 scalar_t__ WLAN_ETHCONV_8021h ; 
 scalar_t__ WLAN_ETHCONV_ENCAP ; 
 int /*<<< orphan*/  WLAN_FSTYPE_DATAONLY ; 
 int /*<<< orphan*/  WLAN_FTYPE_DATA ; 
 int WLAN_IEEE_OUI_LEN ; 
#define  WLAN_MACMODE_ESS_AP 130 
#define  WLAN_MACMODE_ESS_STA 129 
#define  WLAN_MACMODE_IBSS_STA 128 
 int WLAN_SET_FC_FROMDS (int) ; 
 int WLAN_SET_FC_FSTYPE (int /*<<< orphan*/ ) ; 
 int WLAN_SET_FC_FTYPE (int /*<<< orphan*/ ) ; 
 int WLAN_SET_FC_ISWEP (int) ; 
 int WLAN_SET_FC_TODS (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct wlan_ethhdr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_2__*,char*,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * oui_8021h ; 
 int /*<<< orphan*/ * oui_rfc1042 ; 
 scalar_t__ p80211_stt_findproto (scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 void* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 
 int wep_encrypt (struct wlandevice*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int skb_ether_to_p80211(struct wlandevice *wlandev, u32 ethconv,
			struct sk_buff *skb, union p80211_hdr *p80211_hdr,
			struct p80211_metawep *p80211_wep)
{
	__le16 fc;
	u16 proto;
	struct wlan_ethhdr e_hdr;
	struct wlan_llc *e_llc;
	struct wlan_snap *e_snap;
	int foo;

	memcpy(&e_hdr, skb->data, sizeof(e_hdr));

	if (skb->len <= 0) {
		pr_debug("zero-length skb!\n");
		return 1;
	}

	if (ethconv == WLAN_ETHCONV_ENCAP) {	/* simplest case */
		pr_debug("ENCAP len: %d\n", skb->len);
		/* here, we don't care what kind of ether frm. Just stick it */
		/*  in the 80211 payload */
		/* which is to say, leave the skb alone. */
	} else {
		/* step 1: classify ether frame, DIX or 802.3? */
		proto = ntohs(e_hdr.type);
		if (proto <= ETH_DATA_LEN) {
			pr_debug("802.3 len: %d\n", skb->len);
			/* codes <= 1500 reserved for 802.3 lengths */
			/* it's 802.3, pass ether payload unchanged,  */

			/* trim off ethernet header */
			skb_pull(skb, ETH_HLEN);

			/*   leave off any PAD octets.  */
			skb_trim(skb, proto);
		} else {
			pr_debug("DIXII len: %d\n", skb->len);
			/* it's DIXII, time for some conversion */

			/* trim off ethernet header */
			skb_pull(skb, ETH_HLEN);

			/* tack on SNAP */
			e_snap = skb_push(skb, sizeof(struct wlan_snap));
			e_snap->type = htons(proto);
			if (ethconv == WLAN_ETHCONV_8021h &&
			    p80211_stt_findproto(proto)) {
				memcpy(e_snap->oui, oui_8021h,
				       WLAN_IEEE_OUI_LEN);
			} else {
				memcpy(e_snap->oui, oui_rfc1042,
				       WLAN_IEEE_OUI_LEN);
			}

			/* tack on llc */
			e_llc = skb_push(skb, sizeof(struct wlan_llc));
			e_llc->dsap = 0xAA;	/* SNAP, see IEEE 802 */
			e_llc->ssap = 0xAA;
			e_llc->ctl = 0x03;
		}
	}

	/* Set up the 802.11 header */
	/* It's a data frame */
	fc = cpu_to_le16(WLAN_SET_FC_FTYPE(WLAN_FTYPE_DATA) |
			 WLAN_SET_FC_FSTYPE(WLAN_FSTYPE_DATAONLY));

	switch (wlandev->macmode) {
	case WLAN_MACMODE_IBSS_STA:
		memcpy(p80211_hdr->a3.a1, &e_hdr.daddr, ETH_ALEN);
		memcpy(p80211_hdr->a3.a2, wlandev->netdev->dev_addr, ETH_ALEN);
		memcpy(p80211_hdr->a3.a3, wlandev->bssid, ETH_ALEN);
		break;
	case WLAN_MACMODE_ESS_STA:
		fc |= cpu_to_le16(WLAN_SET_FC_TODS(1));
		memcpy(p80211_hdr->a3.a1, wlandev->bssid, ETH_ALEN);
		memcpy(p80211_hdr->a3.a2, wlandev->netdev->dev_addr, ETH_ALEN);
		memcpy(p80211_hdr->a3.a3, &e_hdr.daddr, ETH_ALEN);
		break;
	case WLAN_MACMODE_ESS_AP:
		fc |= cpu_to_le16(WLAN_SET_FC_FROMDS(1));
		memcpy(p80211_hdr->a3.a1, &e_hdr.daddr, ETH_ALEN);
		memcpy(p80211_hdr->a3.a2, wlandev->bssid, ETH_ALEN);
		memcpy(p80211_hdr->a3.a3, &e_hdr.saddr, ETH_ALEN);
		break;
	default:
		netdev_err(wlandev->netdev,
			   "Error: Converting eth to wlan in unknown mode.\n");
		return 1;
	}

	p80211_wep->data = NULL;

	if ((wlandev->hostwep & HOSTWEP_PRIVACYINVOKED) &&
	    (wlandev->hostwep & HOSTWEP_ENCRYPT)) {
		/* XXXX need to pick keynum other than default? */

		p80211_wep->data = kmalloc(skb->len, GFP_ATOMIC);
		if (!p80211_wep->data)
			return -ENOMEM;
		foo = wep_encrypt(wlandev, skb->data, p80211_wep->data,
				  skb->len,
				  wlandev->hostwep & HOSTWEP_DEFAULTKEY_MASK,
				  p80211_wep->iv, p80211_wep->icv);
		if (foo) {
			netdev_warn(wlandev->netdev,
				    "Host en-WEP failed, dropping frame (%d).\n",
				    foo);
			kfree(p80211_wep->data);
			return 2;
		}
		fc |= cpu_to_le16(WLAN_SET_FC_ISWEP(1));
	}

	/*      skb->nh.raw = skb->data; */

	p80211_hdr->a3.fc = fc;
	p80211_hdr->a3.dur = 0;
	p80211_hdr->a3.seq = 0;

	return 0;
}