#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct TYPE_7__ {int /*<<< orphan*/ * challenge; } ;
struct TYPE_10__ {scalar_t__ last_beacon; } ;
struct TYPE_9__ {TYPE_1__ sta; TYPE_4__ ap; } ;
struct sta_info {int listen_interval; int /*<<< orphan*/  users; int /*<<< orphan*/  last_rx; TYPE_3__ u; scalar_t__ flags; scalar_t__ ap; int /*<<< orphan*/  addr; struct lib80211_crypt_data* crypt; } ;
struct sk_buff {int* data; int len; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;
struct lib80211_crypt_data {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr2; } ;
struct hostap_80211_rx_status {int dummy; } ;
struct ap_data {scalar_t__ num_sta; int /*<<< orphan*/  tx_callback_auth; int /*<<< orphan*/  mac_restrictions; int /*<<< orphan*/  sta_table_lock; } ;
struct TYPE_8__ {struct lib80211_crypt_data** crypt; } ;
struct TYPE_11__ {int auth_algs; struct ap_data* ap; TYPE_2__ crypt_info; struct net_device* dev; } ;
typedef  TYPE_5__ local_info_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_AP ; 
 int HZ ; 
 int IEEE80211_FTYPE_MGMT ; 
 int IEEE80211_MGMT_HDR_LEN ; 
 int IEEE80211_STYPE_AUTH ; 
 scalar_t__ MAX_STA_COUNT ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 
 int PRISM2_AUTH_OPEN ; 
 int PRISM2_AUTH_SHARED_KEY ; 
 int WLAN_AUTH_CHALLENGE_LEN ; 
#define  WLAN_AUTH_OPEN 129 
#define  WLAN_AUTH_SHARED_KEY 128 
 scalar_t__ WLAN_EID_CHALLENGE ; 
 int WLAN_STATUS_CHALLENGE_FAIL ; 
 int WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG ; 
 int WLAN_STATUS_SUCCESS ; 
 int WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION ; 
 int WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 scalar_t__ WLAN_STA_AUTH ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct sta_info* ap_add_sta (struct ap_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ap_auth_make_challenge (struct ap_data*) ; 
 scalar_t__ ap_control_mac_deny (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sta_info* ap_get_sta (struct ap_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t hostap_80211_get_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prism2_send_mgmt (struct net_device*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void handle_authen(local_info_t *local, struct sk_buff *skb,
			  struct hostap_80211_rx_status *rx_stats)
{
	struct net_device *dev = local->dev;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;
	size_t hdrlen;
	struct ap_data *ap = local->ap;
	char body[8 + WLAN_AUTH_CHALLENGE_LEN], *challenge = NULL;
	int len, olen;
	u16 auth_alg, auth_transaction, status_code;
	__le16 *pos;
	u16 resp = WLAN_STATUS_SUCCESS;
	struct sta_info *sta = NULL;
	struct lib80211_crypt_data *crypt;
	char *txt = "";

	len = skb->len - IEEE80211_MGMT_HDR_LEN;

	hdrlen = hostap_80211_get_hdrlen(hdr->frame_control);

	if (len < 6) {
		PDEBUG(DEBUG_AP, "%s: handle_authen - too short payload "
		       "(len=%d) from %pM\n", dev->name, len, hdr->addr2);
		return;
	}

	spin_lock_bh(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	if (sta)
		atomic_inc(&sta->users);
	spin_unlock_bh(&local->ap->sta_table_lock);

	if (sta && sta->crypt)
		crypt = sta->crypt;
	else {
		int idx = 0;
		if (skb->len >= hdrlen + 3)
			idx = skb->data[hdrlen + 3] >> 6;
		crypt = local->crypt_info.crypt[idx];
	}

	pos = (__le16 *) (skb->data + IEEE80211_MGMT_HDR_LEN);
	auth_alg = __le16_to_cpu(*pos);
	pos++;
	auth_transaction = __le16_to_cpu(*pos);
	pos++;
	status_code = __le16_to_cpu(*pos);
	pos++;

	if (ether_addr_equal(dev->dev_addr, hdr->addr2) ||
	    ap_control_mac_deny(&ap->mac_restrictions, hdr->addr2)) {
		txt = "authentication denied";
		resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
		goto fail;
	}

	if (((local->auth_algs & PRISM2_AUTH_OPEN) &&
	     auth_alg == WLAN_AUTH_OPEN) ||
	    ((local->auth_algs & PRISM2_AUTH_SHARED_KEY) &&
	     crypt && auth_alg == WLAN_AUTH_SHARED_KEY)) {
	} else {
		txt = "unsupported algorithm";
		resp = WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG;
		goto fail;
	}

	if (len >= 8) {
		u8 *u = (u8 *) pos;
		if (*u == WLAN_EID_CHALLENGE) {
			if (*(u + 1) != WLAN_AUTH_CHALLENGE_LEN) {
				txt = "invalid challenge len";
				resp = WLAN_STATUS_CHALLENGE_FAIL;
				goto fail;
			}
			if (len - 8 < WLAN_AUTH_CHALLENGE_LEN) {
				txt = "challenge underflow";
				resp = WLAN_STATUS_CHALLENGE_FAIL;
				goto fail;
			}
			challenge = (char *) (u + 2);
		}
	}

	if (sta && sta->ap) {
		if (time_after(jiffies, sta->u.ap.last_beacon +
			       (10 * sta->listen_interval * HZ) / 1024)) {
			PDEBUG(DEBUG_AP, "%s: no beacons received for a while,"
			       " assuming AP %pM is now STA\n",
			       dev->name, sta->addr);
			sta->ap = 0;
			sta->flags = 0;
			sta->u.sta.challenge = NULL;
		} else {
			txt = "AP trying to authenticate?";
			resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
			goto fail;
		}
	}

	if ((auth_alg == WLAN_AUTH_OPEN && auth_transaction == 1) ||
	    (auth_alg == WLAN_AUTH_SHARED_KEY &&
	     (auth_transaction == 1 ||
	      (auth_transaction == 3 && sta != NULL &&
	       sta->u.sta.challenge != NULL)))) {
	} else {
		txt = "unknown authentication transaction number";
		resp = WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION;
		goto fail;
	}

	if (sta == NULL) {
		txt = "new STA";

		if (local->ap->num_sta >= MAX_STA_COUNT) {
			/* FIX: might try to remove some old STAs first? */
			txt = "no more room for new STAs";
			resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
			goto fail;
		}

		sta = ap_add_sta(local->ap, hdr->addr2);
		if (sta == NULL) {
			txt = "ap_add_sta failed";
			resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
			goto fail;
		}
	}

	switch (auth_alg) {
	case WLAN_AUTH_OPEN:
		txt = "authOK";
		/* IEEE 802.11 standard is not completely clear about
		 * whether STA is considered authenticated after
		 * authentication OK frame has been send or after it
		 * has been ACKed. In order to reduce interoperability
		 * issues, mark the STA authenticated before ACK. */
		sta->flags |= WLAN_STA_AUTH;
		break;

	case WLAN_AUTH_SHARED_KEY:
		if (auth_transaction == 1) {
			if (sta->u.sta.challenge == NULL) {
				sta->u.sta.challenge =
					ap_auth_make_challenge(local->ap);
				if (sta->u.sta.challenge == NULL) {
					resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
					goto fail;
				}
			}
		} else {
			if (sta->u.sta.challenge == NULL ||
			    challenge == NULL ||
			    memcmp(sta->u.sta.challenge, challenge,
				   WLAN_AUTH_CHALLENGE_LEN) != 0 ||
			    !ieee80211_has_protected(hdr->frame_control)) {
				txt = "challenge response incorrect";
				resp = WLAN_STATUS_CHALLENGE_FAIL;
				goto fail;
			}

			txt = "challenge OK - authOK";
			/* IEEE 802.11 standard is not completely clear about
			 * whether STA is considered authenticated after
			 * authentication OK frame has been send or after it
			 * has been ACKed. In order to reduce interoperability
			 * issues, mark the STA authenticated before ACK. */
			sta->flags |= WLAN_STA_AUTH;
			kfree(sta->u.sta.challenge);
			sta->u.sta.challenge = NULL;
		}
		break;
	}

 fail:
	pos = (__le16 *) body;
	*pos = cpu_to_le16(auth_alg);
	pos++;
	*pos = cpu_to_le16(auth_transaction + 1);
	pos++;
	*pos = cpu_to_le16(resp); /* status_code */
	pos++;
	olen = 6;

	if (resp == WLAN_STATUS_SUCCESS && sta != NULL &&
	    sta->u.sta.challenge != NULL &&
	    auth_alg == WLAN_AUTH_SHARED_KEY && auth_transaction == 1) {
		u8 *tmp = (u8 *) pos;
		*tmp++ = WLAN_EID_CHALLENGE;
		*tmp++ = WLAN_AUTH_CHALLENGE_LEN;
		pos++;
		memcpy(pos, sta->u.sta.challenge, WLAN_AUTH_CHALLENGE_LEN);
		olen += 2 + WLAN_AUTH_CHALLENGE_LEN;
	}

	prism2_send_mgmt(dev, IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_AUTH,
			 body, olen, hdr->addr2, ap->tx_callback_auth);

	if (sta) {
		sta->last_rx = jiffies;
		atomic_dec(&sta->users);
	}

	if (resp) {
		PDEBUG(DEBUG_AP, "%s: %pM auth (alg=%d "
		       "trans#=%d stat=%d len=%d fc=%04x) ==> %d (%s)\n",
		       dev->name, hdr->addr2,
		       auth_alg, auth_transaction, status_code, len,
		       le16_to_cpu(hdr->frame_control), resp, txt);
	}
}