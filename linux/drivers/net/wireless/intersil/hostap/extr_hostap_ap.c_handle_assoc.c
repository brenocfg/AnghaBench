#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct sta_info {int flags; int aid; int /*<<< orphan*/  users; int /*<<< orphan*/  last_rx; int /*<<< orphan*/ * supported_rates; void* listen_interval; void* capability; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr2; } ;
struct hostap_80211_rx_status {int dummy; } ;
struct TYPE_4__ {int tx_rate_control; int basic_rates; TYPE_3__* ap; int /*<<< orphan*/  essid; struct net_device* dev; } ;
typedef  TYPE_1__ local_info_t ;
typedef  unsigned char __le16 ;
struct TYPE_5__ {int /*<<< orphan*/  tx_callback_assoc; int /*<<< orphan*/  sta_table_lock; struct sta_info** sta_aid; } ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int /*<<< orphan*/  DEBUG_AP ; 
 int ETH_ALEN ; 
 int IEEE80211_FTYPE_MGMT ; 
 int IEEE80211_MGMT_HDR_LEN ; 
 int IEEE80211_STYPE_ASSOC_RESP ; 
 int IEEE80211_STYPE_DEAUTH ; 
 int IEEE80211_STYPE_REASSOC_RESP ; 
 int MAX_AID_TABLE_SIZE ; 
 unsigned int MAX_SSID_LEN ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  PDEBUG2 (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ WLAN_CAPABILITY_ESS ; 
 unsigned char WLAN_EID_SSID ; 
 unsigned char WLAN_EID_SUPP_RATES ; 
 int WLAN_RATE_11M ; 
 int WLAN_RATE_1M ; 
 int WLAN_RATE_2M ; 
 int WLAN_RATE_5M5 ; 
 scalar_t__ WLAN_REASON_STA_REQ_ASSOC_WITHOUT_AUTH ; 
 scalar_t__ WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA ; 
 scalar_t__ WLAN_STATUS_ASSOC_DENIED_UNSPEC ; 
 scalar_t__ WLAN_STATUS_SUCCESS ; 
 scalar_t__ WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 int WLAN_STA_AUTH ; 
 unsigned int WLAN_SUPP_RATES_MAX ; 
 void* __le16_to_cpu (unsigned char) ; 
 struct sta_info* ap_get_sta (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned char cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prism2_check_tx_rates (struct sta_info*) ; 
 int /*<<< orphan*/  prism2_send_mgmt (struct net_device*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 unsigned int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_assoc(local_info_t *local, struct sk_buff *skb,
			 struct hostap_80211_rx_status *rx_stats, int reassoc)
{
	struct net_device *dev = local->dev;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;
	char body[12], *p, *lpos;
	int len, left;
	__le16 *pos;
	u16 resp = WLAN_STATUS_SUCCESS;
	struct sta_info *sta = NULL;
	int send_deauth = 0;
	char *txt = "";
	u8 prev_ap[ETH_ALEN];

	left = len = skb->len - IEEE80211_MGMT_HDR_LEN;

	if (len < (reassoc ? 10 : 4)) {
		PDEBUG(DEBUG_AP, "%s: handle_assoc - too short payload "
		       "(len=%d, reassoc=%d) from %pM\n",
		       dev->name, len, reassoc, hdr->addr2);
		return;
	}

	spin_lock_bh(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	if (sta == NULL || (sta->flags & WLAN_STA_AUTH) == 0) {
		spin_unlock_bh(&local->ap->sta_table_lock);
		txt = "trying to associate before authentication";
		send_deauth = 1;
		resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
		sta = NULL; /* do not decrement sta->users */
		goto fail;
	}
	atomic_inc(&sta->users);
	spin_unlock_bh(&local->ap->sta_table_lock);

	pos = (__le16 *) (skb->data + IEEE80211_MGMT_HDR_LEN);
	sta->capability = __le16_to_cpu(*pos);
	pos++; left -= 2;
	sta->listen_interval = __le16_to_cpu(*pos);
	pos++; left -= 2;

	if (reassoc) {
		memcpy(prev_ap, pos, ETH_ALEN);
		pos++; pos++; pos++; left -= 6;
	} else
		eth_zero_addr(prev_ap);

	if (left >= 2) {
		unsigned int ileft;
		unsigned char *u = (unsigned char *) pos;

		if (*u == WLAN_EID_SSID) {
			u++; left--;
			ileft = *u;
			u++; left--;

			if (ileft > left || ileft > MAX_SSID_LEN) {
				txt = "SSID overflow";
				resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
				goto fail;
			}

			if (ileft != strlen(local->essid) ||
			    memcmp(local->essid, u, ileft) != 0) {
				txt = "not our SSID";
				resp = WLAN_STATUS_ASSOC_DENIED_UNSPEC;
				goto fail;
			}

			u += ileft;
			left -= ileft;
		}

		if (left >= 2 && *u == WLAN_EID_SUPP_RATES) {
			u++; left--;
			ileft = *u;
			u++; left--;

			if (ileft > left || ileft == 0 ||
			    ileft > WLAN_SUPP_RATES_MAX) {
				txt = "SUPP_RATES len error";
				resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
				goto fail;
			}

			memset(sta->supported_rates, 0,
			       sizeof(sta->supported_rates));
			memcpy(sta->supported_rates, u, ileft);
			prism2_check_tx_rates(sta);

			u += ileft;
			left -= ileft;
		}

		if (left > 0) {
			PDEBUG(DEBUG_AP, "%s: assoc from %pM"
			       " with extra data (%d bytes) [",
			       dev->name, hdr->addr2, left);
			while (left > 0) {
				PDEBUG2(DEBUG_AP, "<%02x>", *u);
				u++; left--;
			}
			PDEBUG2(DEBUG_AP, "]\n");
		}
	} else {
		txt = "frame underflow";
		resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
		goto fail;
	}

	/* get a unique AID */
	if (sta->aid > 0)
		txt = "OK, old AID";
	else {
		spin_lock_bh(&local->ap->sta_table_lock);
		for (sta->aid = 1; sta->aid <= MAX_AID_TABLE_SIZE; sta->aid++)
			if (local->ap->sta_aid[sta->aid - 1] == NULL)
				break;
		if (sta->aid > MAX_AID_TABLE_SIZE) {
			sta->aid = 0;
			spin_unlock_bh(&local->ap->sta_table_lock);
			resp = WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA;
			txt = "no room for more AIDs";
		} else {
			local->ap->sta_aid[sta->aid - 1] = sta;
			spin_unlock_bh(&local->ap->sta_table_lock);
			txt = "OK, new AID";
		}
	}

 fail:
	pos = (__le16 *) body;

	if (send_deauth) {
		*pos = cpu_to_le16(WLAN_REASON_STA_REQ_ASSOC_WITHOUT_AUTH);
		pos++;
	} else {
		/* FIX: CF-Pollable and CF-PollReq should be set to match the
		 * values in beacons/probe responses */
		/* FIX: how about privacy and WEP? */
		/* capability */
		*pos = cpu_to_le16(WLAN_CAPABILITY_ESS);
		pos++;

		/* status_code */
		*pos = cpu_to_le16(resp);
		pos++;

		*pos = cpu_to_le16((sta && sta->aid > 0 ? sta->aid : 0) |
				     BIT(14) | BIT(15)); /* AID */
		pos++;

		/* Supported rates (Information element) */
		p = (char *) pos;
		*p++ = WLAN_EID_SUPP_RATES;
		lpos = p;
		*p++ = 0; /* len */
		if (local->tx_rate_control & WLAN_RATE_1M) {
			*p++ = local->basic_rates & WLAN_RATE_1M ? 0x82 : 0x02;
			(*lpos)++;
		}
		if (local->tx_rate_control & WLAN_RATE_2M) {
			*p++ = local->basic_rates & WLAN_RATE_2M ? 0x84 : 0x04;
			(*lpos)++;
		}
		if (local->tx_rate_control & WLAN_RATE_5M5) {
			*p++ = local->basic_rates & WLAN_RATE_5M5 ?
				0x8b : 0x0b;
			(*lpos)++;
		}
		if (local->tx_rate_control & WLAN_RATE_11M) {
			*p++ = local->basic_rates & WLAN_RATE_11M ?
				0x96 : 0x16;
			(*lpos)++;
		}
		pos = (__le16 *) p;
	}

	prism2_send_mgmt(dev, IEEE80211_FTYPE_MGMT |
			 (send_deauth ? IEEE80211_STYPE_DEAUTH :
			  (reassoc ? IEEE80211_STYPE_REASSOC_RESP :
			   IEEE80211_STYPE_ASSOC_RESP)),
			 body, (u8 *) pos - (u8 *) body,
			 hdr->addr2,
			 send_deauth ? 0 : local->ap->tx_callback_assoc);

	if (sta) {
		if (resp == WLAN_STATUS_SUCCESS) {
			sta->last_rx = jiffies;
			/* STA will be marked associated from TX callback, if
			 * AssocResp is ACKed */
		}
		atomic_dec(&sta->users);
	}

#if 0
	PDEBUG(DEBUG_AP, "%s: %pM %sassoc (len=%d "
	       "prev_ap=%pM) => %d(%d) (%s)\n",
	       dev->name,
	       hdr->addr2,
	       reassoc ? "re" : "", len,
	       prev_ap,
	       resp, send_deauth, txt);
#endif
}