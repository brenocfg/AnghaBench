#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned int u16 ;
struct mwifiex_private {unsigned int gen_idx; } ;
struct mwifiex_ie {void* ie_length; void* mgmt_subtype_mask; void* ie_index; scalar_t__ ie_buffer; } ;
struct ieee_types_header {int len; int element_id; } ;
struct ieee80211_vendor_ie {int len; int element_id; } ;
struct cfg80211_beacon_data {int tail_len; int /*<<< orphan*/  const* tail; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int IEEE_MAX_IE_SIZE ; 
 unsigned int MGMT_MASK_ASSOC_RESP ; 
 unsigned int MGMT_MASK_BEACON ; 
 unsigned int MGMT_MASK_PROBE_RESP ; 
 unsigned int MWIFIEX_AUTO_IDX_MASK ; 
#define  WLAN_EID_COUNTRY 138 
#define  WLAN_EID_ERP_INFO 137 
#define  WLAN_EID_EXT_SUPP_RATES 136 
#define  WLAN_EID_HT_CAPABILITY 135 
#define  WLAN_EID_HT_OPERATION 134 
#define  WLAN_EID_PWR_CONSTRAINT 133 
#define  WLAN_EID_SSID 132 
#define  WLAN_EID_SUPP_RATES 131 
#define  WLAN_EID_VENDOR_SPECIFIC 130 
#define  WLAN_EID_VHT_CAPABILITY 129 
#define  WLAN_EID_VHT_OPERATION 128 
 int /*<<< orphan*/  WLAN_OUI_MICROSOFT ; 
 int /*<<< orphan*/  WLAN_OUI_TYPE_MICROSOFT_WMM ; 
 int /*<<< orphan*/  WLAN_OUI_TYPE_MICROSOFT_WPA ; 
 scalar_t__ cfg80211_find_vendor_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  kfree (struct mwifiex_ie*) ; 
 struct mwifiex_ie* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct ieee_types_header*,unsigned int) ; 
 scalar_t__ mwifiex_update_uap_custom_ie (struct mwifiex_private*,struct mwifiex_ie*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mwifiex_uap_parse_tail_ies(struct mwifiex_private *priv,
				      struct cfg80211_beacon_data *info)
{
	struct mwifiex_ie *gen_ie;
	struct ieee_types_header *hdr;
	struct ieee80211_vendor_ie *vendorhdr;
	u16 gen_idx = MWIFIEX_AUTO_IDX_MASK, ie_len = 0;
	int left_len, parsed_len = 0;
	unsigned int token_len;
	int err = 0;

	if (!info->tail || !info->tail_len)
		return 0;

	gen_ie = kzalloc(sizeof(*gen_ie), GFP_KERNEL);
	if (!gen_ie)
		return -ENOMEM;

	left_len = info->tail_len;

	/* Many IEs are generated in FW by parsing bss configuration.
	 * Let's not add them here; else we may end up duplicating these IEs
	 */
	while (left_len > sizeof(struct ieee_types_header)) {
		hdr = (void *)(info->tail + parsed_len);
		token_len = hdr->len + sizeof(struct ieee_types_header);
		if (token_len > left_len) {
			err = -EINVAL;
			goto out;
		}

		switch (hdr->element_id) {
		case WLAN_EID_SSID:
		case WLAN_EID_SUPP_RATES:
		case WLAN_EID_COUNTRY:
		case WLAN_EID_PWR_CONSTRAINT:
		case WLAN_EID_ERP_INFO:
		case WLAN_EID_EXT_SUPP_RATES:
		case WLAN_EID_HT_CAPABILITY:
		case WLAN_EID_HT_OPERATION:
		case WLAN_EID_VHT_CAPABILITY:
		case WLAN_EID_VHT_OPERATION:
			break;
		case WLAN_EID_VENDOR_SPECIFIC:
			/* Skip only Microsoft WMM IE */
			if (cfg80211_find_vendor_ie(WLAN_OUI_MICROSOFT,
						    WLAN_OUI_TYPE_MICROSOFT_WMM,
						    (const u8 *)hdr,
						    token_len))
				break;
			/* fall through */
		default:
			if (ie_len + token_len > IEEE_MAX_IE_SIZE) {
				err = -EINVAL;
				goto out;
			}
			memcpy(gen_ie->ie_buffer + ie_len, hdr, token_len);
			ie_len += token_len;
			break;
		}
		left_len -= token_len;
		parsed_len += token_len;
	}

	/* parse only WPA vendor IE from tail, WMM IE is configured by
	 * bss_config command
	 */
	vendorhdr = (void *)cfg80211_find_vendor_ie(WLAN_OUI_MICROSOFT,
						    WLAN_OUI_TYPE_MICROSOFT_WPA,
						    info->tail, info->tail_len);
	if (vendorhdr) {
		token_len = vendorhdr->len + sizeof(struct ieee_types_header);
		if (ie_len + token_len > IEEE_MAX_IE_SIZE) {
			err = -EINVAL;
			goto out;
		}
		memcpy(gen_ie->ie_buffer + ie_len, vendorhdr, token_len);
		ie_len += token_len;
	}

	if (!ie_len)
		goto out;

	gen_ie->ie_index = cpu_to_le16(gen_idx);
	gen_ie->mgmt_subtype_mask = cpu_to_le16(MGMT_MASK_BEACON |
						MGMT_MASK_PROBE_RESP |
						MGMT_MASK_ASSOC_RESP);
	gen_ie->ie_length = cpu_to_le16(ie_len);

	if (mwifiex_update_uap_custom_ie(priv, gen_ie, &gen_idx, NULL, NULL,
					 NULL, NULL)) {
		err = -EINVAL;
		goto out;
	}

	priv->gen_idx = gen_idx;

 out:
	kfree(gen_ie);
	return err;
}