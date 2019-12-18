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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct mwifiex_private {int wmm_enabled; int ap_11n_enabled; int ap_11ac_enabled; int /*<<< orphan*/  adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  len; } ;
struct mwifiex_ie_types_data {TYPE_1__ header; } ;
struct TYPE_4__ {int element_id; int /*<<< orphan*/  len; } ;
struct ieee_types_wmm_parameter {int qos_info_bitmap; TYPE_2__ vend_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT ; 
 int /*<<< orphan*/  EVT_D ; 
 int IEEE80211_WMM_IE_AP_QOSINFO_PARAM_SET_CNT_MASK ; 
 int /*<<< orphan*/  MWIFIEX_BSS_START_EVT_FIX_SIZE ; 
#define  WLAN_EID_HT_CAPABILITY 130 
#define  WLAN_EID_VENDOR_SPECIFIC 129 
#define  WLAN_EID_VHT_CAPABILITY 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mwifiex_dbg_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mwifiex_wmm_setup_ac_downgrade (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_wmm_setup_queue_priorities (struct mwifiex_private*,struct ieee_types_wmm_parameter*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_check_uap_capabilities(struct mwifiex_private *priv,
					  struct sk_buff *event)
{
	int evt_len;
	u8 *curr;
	u16 tlv_len;
	struct mwifiex_ie_types_data *tlv_hdr;
	struct ieee_types_wmm_parameter *wmm_param_ie = NULL;
	int mask = IEEE80211_WMM_IE_AP_QOSINFO_PARAM_SET_CNT_MASK;

	priv->wmm_enabled = false;
	skb_pull(event, MWIFIEX_BSS_START_EVT_FIX_SIZE);
	evt_len = event->len;
	curr = event->data;

	mwifiex_dbg_dump(priv->adapter, EVT_D, "uap capabilities:",
			 event->data, event->len);

	skb_push(event, MWIFIEX_BSS_START_EVT_FIX_SIZE);

	while ((evt_len >= sizeof(tlv_hdr->header))) {
		tlv_hdr = (struct mwifiex_ie_types_data *)curr;
		tlv_len = le16_to_cpu(tlv_hdr->header.len);

		if (evt_len < tlv_len + sizeof(tlv_hdr->header))
			break;

		switch (le16_to_cpu(tlv_hdr->header.type)) {
		case WLAN_EID_HT_CAPABILITY:
			priv->ap_11n_enabled = true;
			break;

		case WLAN_EID_VHT_CAPABILITY:
			priv->ap_11ac_enabled = true;
			break;

		case WLAN_EID_VENDOR_SPECIFIC:
			/* Point the regular IEEE IE 2 bytes into the Marvell IE
			 * and setup the IEEE IE type and length byte fields
			 */
			wmm_param_ie = (void *)(curr + 2);
			wmm_param_ie->vend_hdr.len = (u8)tlv_len;
			wmm_param_ie->vend_hdr.element_id =
						WLAN_EID_VENDOR_SPECIFIC;
			mwifiex_dbg(priv->adapter, EVENT,
				    "info: check uap capabilities:\t"
				    "wmm parameter set count: %d\n",
				    wmm_param_ie->qos_info_bitmap & mask);

			mwifiex_wmm_setup_ac_downgrade(priv);
			priv->wmm_enabled = true;
			mwifiex_wmm_setup_queue_priorities(priv, wmm_param_ie);
			break;

		default:
			break;
		}

		curr += (tlv_len + sizeof(tlv_hdr->header));
		evt_len -= (tlv_len + sizeof(tlv_hdr->header));
	}

	return 0;
}