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
typedef  int uint ;
typedef  int u8 ;
struct rtw_ieee802_11_elems {int* ssid; int ssid_len; int* supp_rates; int supp_rates_len; int* fh_params; int fh_params_len; int* ds_params; int ds_params_len; int* cf_params; int cf_params_len; int* tim; int tim_len; int* ibss_params; int ibss_params_len; int* challenge; int challenge_len; int* erp_info; int erp_info_len; int* ext_supp_rates; int ext_supp_rates_len; int* rsn_ie; int rsn_ie_len; int* power_cap; int power_cap_len; int* supp_channels; int supp_channels_len; int* mdie; int mdie_len; int* ftie; int ftie_len; int* timeout_int; int timeout_int_len; int* ht_capabilities; int ht_capabilities_len; int* ht_operation; int ht_operation_len; } ;
typedef  enum parse_res { ____Placeholder_parse_res } parse_res ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*,int,int,...) ; 
 int ParseFailed ; 
 int ParseOK ; 
 int ParseUnknown ; 
#define  WLAN_EID_CF_PARAMS 146 
#define  WLAN_EID_CHALLENGE 145 
#define  WLAN_EID_DS_PARAMS 144 
#define  WLAN_EID_ERP_INFO 143 
#define  WLAN_EID_EXT_SUPP_RATES 142 
#define  WLAN_EID_FAST_BSS_TRANSITION 141 
#define  WLAN_EID_FH_PARAMS 140 
#define  WLAN_EID_HT_CAPABILITY 139 
#define  WLAN_EID_HT_OPERATION 138 
#define  WLAN_EID_IBSS_PARAMS 137 
#define  WLAN_EID_MOBILITY_DOMAIN 136 
#define  WLAN_EID_PWR_CAPABILITY 135 
#define  WLAN_EID_RSN 134 
#define  WLAN_EID_SSID 133 
#define  WLAN_EID_SUPPORTED_CHANNELS 132 
#define  WLAN_EID_SUPP_RATES 131 
#define  WLAN_EID_TIM 130 
#define  WLAN_EID_TIMEOUT_INTERVAL 129 
#define  WLAN_EID_VENDOR_SPECIFIC 128 
 int /*<<< orphan*/  memset (struct rtw_ieee802_11_elems*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_ieee802_11_parse_vendor_specific (int*,int,struct rtw_ieee802_11_elems*,int) ; 

enum parse_res rtw_ieee802_11_parse_elems(u8 *start, uint len,
				struct rtw_ieee802_11_elems *elems,
				int show_errors)
{
	uint left = len;
	u8 *pos = start;
	int unknown = 0;

	memset(elems, 0, sizeof(*elems));

	while (left >= 2) {
		u8 id, elen;

		id = *pos++;
		elen = *pos++;
		left -= 2;

		if (elen > left) {
			if (show_errors) {
				DBG_88E("IEEE 802.11 element parse failed (id=%d elen=%d left=%lu)\n",
					id, elen, (unsigned long)left);
			}
			return ParseFailed;
		}

		switch (id) {
		case WLAN_EID_SSID:
			elems->ssid = pos;
			elems->ssid_len = elen;
			break;
		case WLAN_EID_SUPP_RATES:
			elems->supp_rates = pos;
			elems->supp_rates_len = elen;
			break;
		case WLAN_EID_FH_PARAMS:
			elems->fh_params = pos;
			elems->fh_params_len = elen;
			break;
		case WLAN_EID_DS_PARAMS:
			elems->ds_params = pos;
			elems->ds_params_len = elen;
			break;
		case WLAN_EID_CF_PARAMS:
			elems->cf_params = pos;
			elems->cf_params_len = elen;
			break;
		case WLAN_EID_TIM:
			elems->tim = pos;
			elems->tim_len = elen;
			break;
		case WLAN_EID_IBSS_PARAMS:
			elems->ibss_params = pos;
			elems->ibss_params_len = elen;
			break;
		case WLAN_EID_CHALLENGE:
			elems->challenge = pos;
			elems->challenge_len = elen;
			break;
		case WLAN_EID_ERP_INFO:
			elems->erp_info = pos;
			elems->erp_info_len = elen;
			break;
		case WLAN_EID_EXT_SUPP_RATES:
			elems->ext_supp_rates = pos;
			elems->ext_supp_rates_len = elen;
			break;
		case WLAN_EID_VENDOR_SPECIFIC:
			if (rtw_ieee802_11_parse_vendor_specific(pos, elen, elems, show_errors))
				unknown++;
			break;
		case WLAN_EID_RSN:
			elems->rsn_ie = pos;
			elems->rsn_ie_len = elen;
			break;
		case WLAN_EID_PWR_CAPABILITY:
			elems->power_cap = pos;
			elems->power_cap_len = elen;
			break;
		case WLAN_EID_SUPPORTED_CHANNELS:
			elems->supp_channels = pos;
			elems->supp_channels_len = elen;
			break;
		case WLAN_EID_MOBILITY_DOMAIN:
			elems->mdie = pos;
			elems->mdie_len = elen;
			break;
		case WLAN_EID_FAST_BSS_TRANSITION:
			elems->ftie = pos;
			elems->ftie_len = elen;
			break;
		case WLAN_EID_TIMEOUT_INTERVAL:
			elems->timeout_int = pos;
			elems->timeout_int_len = elen;
			break;
		case WLAN_EID_HT_CAPABILITY:
			elems->ht_capabilities = pos;
			elems->ht_capabilities_len = elen;
			break;
		case WLAN_EID_HT_OPERATION:
			elems->ht_operation = pos;
			elems->ht_operation_len = elen;
			break;
		default:
			unknown++;
			if (!show_errors)
				break;
			DBG_88E("IEEE 802.11 element parse ignored unknown element (id=%d elen=%d)\n",
				id, elen);
			break;
		}
		left -= elen;
		pos += elen;
	}
	if (left)
		return ParseFailed;
	return unknown ? ParseUnknown : ParseOK;
}