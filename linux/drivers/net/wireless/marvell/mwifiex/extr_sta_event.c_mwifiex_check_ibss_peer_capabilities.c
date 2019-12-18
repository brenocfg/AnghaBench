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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct mwifiex_sta_node {int is_11n_enabled; int is_11ac_enabled; void* max_amsdu; } ;
struct mwifiex_private {int /*<<< orphan*/  adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
struct mwifiex_ie_types_mgmt_frame {TYPE_1__ header; } ;
struct ieee_types_header {int len; int element_id; } ;
struct ieee80211_vht_cap {int /*<<< orphan*/  vht_cap_info; } ;
struct ieee80211_ht_cap {int /*<<< orphan*/  cap_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_D ; 
 int IEEE80211_HT_CAP_MAX_AMSDU ; 
#define  IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454 132 
#define  IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_3895 131 
#define  IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991 130 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  MSG ; 
 int /*<<< orphan*/  MWIFIEX_IBSS_CONNECT_EVT_FIX_SIZE ; 
 void* MWIFIEX_TX_DATA_BUF_SIZE_12K ; 
 void* MWIFIEX_TX_DATA_BUF_SIZE_4K ; 
 void* MWIFIEX_TX_DATA_BUF_SIZE_8K ; 
 int TLV_TYPE_UAP_MGMT_FRAME ; 
#define  WLAN_EID_HT_CAPABILITY 129 
#define  WLAN_EID_VHT_CAPABILITY 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mwifiex_dbg_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_check_ibss_peer_capabilities(struct mwifiex_private *priv,
					        struct mwifiex_sta_node *sta_ptr,
					        struct sk_buff *event)
{
	int evt_len, ele_len;
	u8 *curr;
	struct ieee_types_header *ele_hdr;
	struct mwifiex_ie_types_mgmt_frame *tlv_mgmt_frame;
	const struct ieee80211_ht_cap *ht_cap;
	const struct ieee80211_vht_cap *vht_cap;

	skb_pull(event, MWIFIEX_IBSS_CONNECT_EVT_FIX_SIZE);
	evt_len = event->len;
	curr = event->data;

	mwifiex_dbg_dump(priv->adapter, EVT_D, "ibss peer capabilities:",
			 event->data, event->len);

	skb_push(event, MWIFIEX_IBSS_CONNECT_EVT_FIX_SIZE);

	tlv_mgmt_frame = (void *)curr;
	if (evt_len >= sizeof(*tlv_mgmt_frame) &&
	    le16_to_cpu(tlv_mgmt_frame->header.type) ==
	    TLV_TYPE_UAP_MGMT_FRAME) {
		/* Locate curr pointer to the start of beacon tlv,
		 * timestamp 8 bytes, beacon intervel 2 bytes,
		 * capability info 2 bytes, totally 12 byte beacon header
		 */
		evt_len = le16_to_cpu(tlv_mgmt_frame->header.len);
		curr += (sizeof(*tlv_mgmt_frame) + 12);
	} else {
		mwifiex_dbg(priv->adapter, MSG,
			    "management frame tlv not found!\n");
		return 0;
	}

	while (evt_len >= sizeof(*ele_hdr)) {
		ele_hdr = (struct ieee_types_header *)curr;
		ele_len = ele_hdr->len;

		if (evt_len < ele_len + sizeof(*ele_hdr))
			break;

		switch (ele_hdr->element_id) {
		case WLAN_EID_HT_CAPABILITY:
			sta_ptr->is_11n_enabled = true;
			ht_cap = (void *)(ele_hdr + 2);
			sta_ptr->max_amsdu = le16_to_cpu(ht_cap->cap_info) &
				IEEE80211_HT_CAP_MAX_AMSDU ?
				MWIFIEX_TX_DATA_BUF_SIZE_8K :
				MWIFIEX_TX_DATA_BUF_SIZE_4K;
			mwifiex_dbg(priv->adapter, INFO,
				    "11n enabled!, max_amsdu : %d\n",
				    sta_ptr->max_amsdu);
			break;

		case WLAN_EID_VHT_CAPABILITY:
			sta_ptr->is_11ac_enabled = true;
			vht_cap = (void *)(ele_hdr + 2);
			/* check VHT MAXMPDU capability */
			switch (le32_to_cpu(vht_cap->vht_cap_info) & 0x3) {
			case IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454:
				sta_ptr->max_amsdu =
					MWIFIEX_TX_DATA_BUF_SIZE_12K;
				break;
			case IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991:
				sta_ptr->max_amsdu =
					MWIFIEX_TX_DATA_BUF_SIZE_8K;
				break;
			case IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_3895:
				sta_ptr->max_amsdu =
					MWIFIEX_TX_DATA_BUF_SIZE_4K;
			default:
				break;
			}

			mwifiex_dbg(priv->adapter, INFO,
				    "11ac enabled!, max_amsdu : %d\n",
				    sta_ptr->max_amsdu);
			break;
		default:
			break;
		}

		curr += (ele_len + sizeof(*ele_hdr));
		evt_len -= (ele_len + sizeof(*ele_hdr));
	}

	return 0;
}