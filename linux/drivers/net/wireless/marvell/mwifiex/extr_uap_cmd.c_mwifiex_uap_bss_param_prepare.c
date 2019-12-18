#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_19__ ;
typedef  struct TYPE_28__   TYPE_18__ ;
typedef  struct TYPE_27__   TYPE_17__ ;
typedef  struct TYPE_26__   TYPE_16__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int u16 ;
struct TYPE_29__ {int qos_info; } ;
struct TYPE_25__ {int /*<<< orphan*/  antenna_selection_info; int /*<<< orphan*/  tx_BF_cap_info; int /*<<< orphan*/  extended_ht_cap_info; TYPE_19__ mcs; int /*<<< orphan*/  ampdu_params_info; scalar_t__ cap_info; } ;
struct TYPE_31__ {int ssid_len; TYPE_19__* ssid; } ;
struct mwifiex_uap_bss_param {scalar_t__ channel; int band_cfg; int beacon_period; scalar_t__ dtim_period; int rts_threshold; int frag_threshold; scalar_t__ retry_limit; int protocol; scalar_t__ auth_mode; scalar_t__ ps_sta_ao_timer; scalar_t__ power_constraint; scalar_t__ sta_ao_timer; TYPE_19__ wmm_info; TYPE_15__ ht_cap; scalar_t__* rates; int /*<<< orphan*/  bcast_ssid_ctl; TYPE_2__ ssid; } ;
struct TYPE_26__ {void* len; void* type; } ;
struct mwifiex_ie_types_wmmcap {int /*<<< orphan*/  wmm_info; TYPE_16__ header; } ;
struct TYPE_24__ {int /*<<< orphan*/  antenna_selection_info; int /*<<< orphan*/  tx_BF_cap_info; int /*<<< orphan*/  extended_ht_cap_info; int /*<<< orphan*/  mcs; int /*<<< orphan*/  ampdu_params_info; scalar_t__ cap_info; } ;
struct TYPE_23__ {void* len; void* type; } ;
struct mwifiex_ie_types_htcap {TYPE_14__ ht_cap; TYPE_13__ header; } ;
struct mwifiex_ie_types_header {int dummy; } ;
struct ieee80211_mcs_info {int dummy; } ;
struct ieee80211_ht_cap {int dummy; } ;
struct TYPE_30__ {void* len; void* type; } ;
struct host_cmd_tlv_ssid {int /*<<< orphan*/ * ssid; TYPE_1__ header; } ;
struct TYPE_37__ {void* len; void* type; } ;
struct host_cmd_tlv_rts_threshold {void* rts_thr; TYPE_8__ header; } ;
struct TYPE_20__ {void* len; void* type; } ;
struct host_cmd_tlv_retry_limit {void* limit; TYPE_10__ header; } ;
struct TYPE_33__ {void* len; void* type; } ;
struct host_cmd_tlv_rates {TYPE_4__ header; scalar_t__* rates; } ;
struct TYPE_27__ {void* len; void* type; } ;
struct host_cmd_tlv_power_constraint {scalar_t__ constraint; TYPE_17__ header; } ;
struct TYPE_38__ {void* len; void* type; } ;
struct host_cmd_tlv_frag_threshold {void* frag_thr; TYPE_9__ header; } ;
struct TYPE_22__ {void* len; void* type; } ;
struct host_cmd_tlv_encrypt_protocol {void* proto; TYPE_12__ header; } ;
struct TYPE_36__ {void* len; void* type; } ;
struct host_cmd_tlv_dtim_period {scalar_t__ period; TYPE_7__ header; } ;
struct TYPE_34__ {void* len; void* type; } ;
struct host_cmd_tlv_channel_band {int band_config; scalar_t__ channel; TYPE_5__ header; } ;
struct TYPE_35__ {void* len; void* type; } ;
struct host_cmd_tlv_beacon_period {void* period; TYPE_6__ header; } ;
struct TYPE_32__ {void* len; void* type; } ;
struct host_cmd_tlv_bcast_ssid {int /*<<< orphan*/  bcast_ctl; TYPE_3__ header; } ;
struct TYPE_21__ {void* len; void* type; } ;
struct host_cmd_tlv_auth_type {void* auth_type; TYPE_11__ header; } ;
struct TYPE_28__ {void* len; void* type; } ;
struct host_cmd_tlv_ageout_timer {void* sta_ao_timer; TYPE_18__ header; } ;

/* Variables and functions */
 int BAND_CONFIG_A ; 
 int BAND_CONFIG_BG ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int MAX_BEACON_PERIOD ; 
 scalar_t__ MAX_CHANNEL_BAND_A ; 
 scalar_t__ MAX_CHANNEL_BAND_BG ; 
 scalar_t__ MAX_DTIM_PERIOD ; 
 int MIN_BEACON_PERIOD ; 
 scalar_t__ MIN_DTIM_PERIOD ; 
 scalar_t__ MWIFIEX_AUTH_MODE_AUTO ; 
 int MWIFIEX_FRAG_MAX_VALUE ; 
 int MWIFIEX_FRAG_MIN_VALUE ; 
 scalar_t__ MWIFIEX_RETRY_LIMIT ; 
 int MWIFIEX_RTS_MAX_VALUE ; 
 int MWIFIEX_SUPPORTED_RATES ; 
 int PROTOCOL_EAP ; 
 int PROTOCOL_WPA ; 
 int PROTOCOL_WPA2 ; 
 int TLV_TYPE_AUTH_TYPE ; 
 int TLV_TYPE_CHANNELBANDLIST ; 
 int TLV_TYPE_PWR_CONSTRAINT ; 
 int TLV_TYPE_UAP_AO_TIMER ; 
 int TLV_TYPE_UAP_BCAST_SSID ; 
 int TLV_TYPE_UAP_BEACON_PERIOD ; 
 int TLV_TYPE_UAP_DTIM_PERIOD ; 
 int TLV_TYPE_UAP_ENCRY_PROTOCOL ; 
 int TLV_TYPE_UAP_FRAG_THRESHOLD ; 
 int TLV_TYPE_UAP_PS_AO_TIMER ; 
 int TLV_TYPE_UAP_RATES ; 
 int TLV_TYPE_UAP_RETRY_LIMIT ; 
 int TLV_TYPE_UAP_RTS_THRESHOLD ; 
 int TLV_TYPE_UAP_SSID ; 
 scalar_t__ WLAN_AUTH_SHARED_KEY ; 
 int WLAN_EID_HT_CAPABILITY ; 
 int WLAN_EID_VENDOR_SPECIFIC ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_19__*,int) ; 
 int /*<<< orphan*/  mwifiex_uap_bss_wep (void***,void*,int*) ; 
 int /*<<< orphan*/  mwifiex_uap_bss_wpa (void***,void*,int*) ; 

__attribute__((used)) static int
mwifiex_uap_bss_param_prepare(u8 *tlv, void *cmd_buf, u16 *param_size)
{
	struct host_cmd_tlv_dtim_period *dtim_period;
	struct host_cmd_tlv_beacon_period *beacon_period;
	struct host_cmd_tlv_ssid *ssid;
	struct host_cmd_tlv_bcast_ssid *bcast_ssid;
	struct host_cmd_tlv_channel_band *chan_band;
	struct host_cmd_tlv_frag_threshold *frag_threshold;
	struct host_cmd_tlv_rts_threshold *rts_threshold;
	struct host_cmd_tlv_retry_limit *retry_limit;
	struct host_cmd_tlv_encrypt_protocol *encrypt_protocol;
	struct host_cmd_tlv_auth_type *auth_type;
	struct host_cmd_tlv_rates *tlv_rates;
	struct host_cmd_tlv_ageout_timer *ao_timer, *ps_ao_timer;
	struct host_cmd_tlv_power_constraint *pwr_ct;
	struct mwifiex_ie_types_htcap *htcap;
	struct mwifiex_ie_types_wmmcap *wmm_cap;
	struct mwifiex_uap_bss_param *bss_cfg = cmd_buf;
	int i;
	u16 cmd_size = *param_size;

	if (bss_cfg->ssid.ssid_len) {
		ssid = (struct host_cmd_tlv_ssid *)tlv;
		ssid->header.type = cpu_to_le16(TLV_TYPE_UAP_SSID);
		ssid->header.len = cpu_to_le16((u16)bss_cfg->ssid.ssid_len);
		memcpy(ssid->ssid, bss_cfg->ssid.ssid, bss_cfg->ssid.ssid_len);
		cmd_size += sizeof(struct mwifiex_ie_types_header) +
			    bss_cfg->ssid.ssid_len;
		tlv += sizeof(struct mwifiex_ie_types_header) +
				bss_cfg->ssid.ssid_len;

		bcast_ssid = (struct host_cmd_tlv_bcast_ssid *)tlv;
		bcast_ssid->header.type = cpu_to_le16(TLV_TYPE_UAP_BCAST_SSID);
		bcast_ssid->header.len =
				cpu_to_le16(sizeof(bcast_ssid->bcast_ctl));
		bcast_ssid->bcast_ctl = bss_cfg->bcast_ssid_ctl;
		cmd_size += sizeof(struct host_cmd_tlv_bcast_ssid);
		tlv += sizeof(struct host_cmd_tlv_bcast_ssid);
	}
	if (bss_cfg->rates[0]) {
		tlv_rates = (struct host_cmd_tlv_rates *)tlv;
		tlv_rates->header.type = cpu_to_le16(TLV_TYPE_UAP_RATES);

		for (i = 0; i < MWIFIEX_SUPPORTED_RATES && bss_cfg->rates[i];
		     i++)
			tlv_rates->rates[i] = bss_cfg->rates[i];

		tlv_rates->header.len = cpu_to_le16(i);
		cmd_size += sizeof(struct host_cmd_tlv_rates) + i;
		tlv += sizeof(struct host_cmd_tlv_rates) + i;
	}
	if (bss_cfg->channel &&
	    (((bss_cfg->band_cfg & BIT(0)) == BAND_CONFIG_BG &&
	      bss_cfg->channel <= MAX_CHANNEL_BAND_BG) ||
	    ((bss_cfg->band_cfg & BIT(0)) == BAND_CONFIG_A &&
	     bss_cfg->channel <= MAX_CHANNEL_BAND_A))) {
		chan_band = (struct host_cmd_tlv_channel_band *)tlv;
		chan_band->header.type = cpu_to_le16(TLV_TYPE_CHANNELBANDLIST);
		chan_band->header.len =
			cpu_to_le16(sizeof(struct host_cmd_tlv_channel_band) -
				    sizeof(struct mwifiex_ie_types_header));
		chan_band->band_config = bss_cfg->band_cfg;
		chan_band->channel = bss_cfg->channel;
		cmd_size += sizeof(struct host_cmd_tlv_channel_band);
		tlv += sizeof(struct host_cmd_tlv_channel_band);
	}
	if (bss_cfg->beacon_period >= MIN_BEACON_PERIOD &&
	    bss_cfg->beacon_period <= MAX_BEACON_PERIOD) {
		beacon_period = (struct host_cmd_tlv_beacon_period *)tlv;
		beacon_period->header.type =
					cpu_to_le16(TLV_TYPE_UAP_BEACON_PERIOD);
		beacon_period->header.len =
			cpu_to_le16(sizeof(struct host_cmd_tlv_beacon_period) -
				    sizeof(struct mwifiex_ie_types_header));
		beacon_period->period = cpu_to_le16(bss_cfg->beacon_period);
		cmd_size += sizeof(struct host_cmd_tlv_beacon_period);
		tlv += sizeof(struct host_cmd_tlv_beacon_period);
	}
	if (bss_cfg->dtim_period >= MIN_DTIM_PERIOD &&
	    bss_cfg->dtim_period <= MAX_DTIM_PERIOD) {
		dtim_period = (struct host_cmd_tlv_dtim_period *)tlv;
		dtim_period->header.type =
			cpu_to_le16(TLV_TYPE_UAP_DTIM_PERIOD);
		dtim_period->header.len =
			cpu_to_le16(sizeof(struct host_cmd_tlv_dtim_period) -
				    sizeof(struct mwifiex_ie_types_header));
		dtim_period->period = bss_cfg->dtim_period;
		cmd_size += sizeof(struct host_cmd_tlv_dtim_period);
		tlv += sizeof(struct host_cmd_tlv_dtim_period);
	}
	if (bss_cfg->rts_threshold <= MWIFIEX_RTS_MAX_VALUE) {
		rts_threshold = (struct host_cmd_tlv_rts_threshold *)tlv;
		rts_threshold->header.type =
					cpu_to_le16(TLV_TYPE_UAP_RTS_THRESHOLD);
		rts_threshold->header.len =
			cpu_to_le16(sizeof(struct host_cmd_tlv_rts_threshold) -
				    sizeof(struct mwifiex_ie_types_header));
		rts_threshold->rts_thr = cpu_to_le16(bss_cfg->rts_threshold);
		cmd_size += sizeof(struct host_cmd_tlv_frag_threshold);
		tlv += sizeof(struct host_cmd_tlv_frag_threshold);
	}
	if ((bss_cfg->frag_threshold >= MWIFIEX_FRAG_MIN_VALUE) &&
	    (bss_cfg->frag_threshold <= MWIFIEX_FRAG_MAX_VALUE)) {
		frag_threshold = (struct host_cmd_tlv_frag_threshold *)tlv;
		frag_threshold->header.type =
				cpu_to_le16(TLV_TYPE_UAP_FRAG_THRESHOLD);
		frag_threshold->header.len =
			cpu_to_le16(sizeof(struct host_cmd_tlv_frag_threshold) -
				    sizeof(struct mwifiex_ie_types_header));
		frag_threshold->frag_thr = cpu_to_le16(bss_cfg->frag_threshold);
		cmd_size += sizeof(struct host_cmd_tlv_frag_threshold);
		tlv += sizeof(struct host_cmd_tlv_frag_threshold);
	}
	if (bss_cfg->retry_limit <= MWIFIEX_RETRY_LIMIT) {
		retry_limit = (struct host_cmd_tlv_retry_limit *)tlv;
		retry_limit->header.type =
			cpu_to_le16(TLV_TYPE_UAP_RETRY_LIMIT);
		retry_limit->header.len =
			cpu_to_le16(sizeof(struct host_cmd_tlv_retry_limit) -
				    sizeof(struct mwifiex_ie_types_header));
		retry_limit->limit = (u8)bss_cfg->retry_limit;
		cmd_size += sizeof(struct host_cmd_tlv_retry_limit);
		tlv += sizeof(struct host_cmd_tlv_retry_limit);
	}
	if ((bss_cfg->protocol & PROTOCOL_WPA) ||
	    (bss_cfg->protocol & PROTOCOL_WPA2) ||
	    (bss_cfg->protocol & PROTOCOL_EAP))
		mwifiex_uap_bss_wpa(&tlv, cmd_buf, &cmd_size);
	else
		mwifiex_uap_bss_wep(&tlv, cmd_buf, &cmd_size);

	if ((bss_cfg->auth_mode <= WLAN_AUTH_SHARED_KEY) ||
	    (bss_cfg->auth_mode == MWIFIEX_AUTH_MODE_AUTO)) {
		auth_type = (struct host_cmd_tlv_auth_type *)tlv;
		auth_type->header.type = cpu_to_le16(TLV_TYPE_AUTH_TYPE);
		auth_type->header.len =
			cpu_to_le16(sizeof(struct host_cmd_tlv_auth_type) -
			sizeof(struct mwifiex_ie_types_header));
		auth_type->auth_type = (u8)bss_cfg->auth_mode;
		cmd_size += sizeof(struct host_cmd_tlv_auth_type);
		tlv += sizeof(struct host_cmd_tlv_auth_type);
	}
	if (bss_cfg->protocol) {
		encrypt_protocol = (struct host_cmd_tlv_encrypt_protocol *)tlv;
		encrypt_protocol->header.type =
			cpu_to_le16(TLV_TYPE_UAP_ENCRY_PROTOCOL);
		encrypt_protocol->header.len =
			cpu_to_le16(sizeof(struct host_cmd_tlv_encrypt_protocol)
			- sizeof(struct mwifiex_ie_types_header));
		encrypt_protocol->proto = cpu_to_le16(bss_cfg->protocol);
		cmd_size += sizeof(struct host_cmd_tlv_encrypt_protocol);
		tlv += sizeof(struct host_cmd_tlv_encrypt_protocol);
	}

	if (bss_cfg->ht_cap.cap_info) {
		htcap = (struct mwifiex_ie_types_htcap *)tlv;
		htcap->header.type = cpu_to_le16(WLAN_EID_HT_CAPABILITY);
		htcap->header.len =
				cpu_to_le16(sizeof(struct ieee80211_ht_cap));
		htcap->ht_cap.cap_info = bss_cfg->ht_cap.cap_info;
		htcap->ht_cap.ampdu_params_info =
					     bss_cfg->ht_cap.ampdu_params_info;
		memcpy(&htcap->ht_cap.mcs, &bss_cfg->ht_cap.mcs,
		       sizeof(struct ieee80211_mcs_info));
		htcap->ht_cap.extended_ht_cap_info =
					bss_cfg->ht_cap.extended_ht_cap_info;
		htcap->ht_cap.tx_BF_cap_info = bss_cfg->ht_cap.tx_BF_cap_info;
		htcap->ht_cap.antenna_selection_info =
					bss_cfg->ht_cap.antenna_selection_info;
		cmd_size += sizeof(struct mwifiex_ie_types_htcap);
		tlv += sizeof(struct mwifiex_ie_types_htcap);
	}

	if (bss_cfg->wmm_info.qos_info != 0xFF) {
		wmm_cap = (struct mwifiex_ie_types_wmmcap *)tlv;
		wmm_cap->header.type = cpu_to_le16(WLAN_EID_VENDOR_SPECIFIC);
		wmm_cap->header.len = cpu_to_le16(sizeof(wmm_cap->wmm_info));
		memcpy(&wmm_cap->wmm_info, &bss_cfg->wmm_info,
		       sizeof(wmm_cap->wmm_info));
		cmd_size += sizeof(struct mwifiex_ie_types_wmmcap);
		tlv += sizeof(struct mwifiex_ie_types_wmmcap);
	}

	if (bss_cfg->sta_ao_timer) {
		ao_timer = (struct host_cmd_tlv_ageout_timer *)tlv;
		ao_timer->header.type = cpu_to_le16(TLV_TYPE_UAP_AO_TIMER);
		ao_timer->header.len = cpu_to_le16(sizeof(*ao_timer) -
					sizeof(struct mwifiex_ie_types_header));
		ao_timer->sta_ao_timer = cpu_to_le32(bss_cfg->sta_ao_timer);
		cmd_size += sizeof(*ao_timer);
		tlv += sizeof(*ao_timer);
	}

	if (bss_cfg->power_constraint) {
		pwr_ct = (void *)tlv;
		pwr_ct->header.type = cpu_to_le16(TLV_TYPE_PWR_CONSTRAINT);
		pwr_ct->header.len = cpu_to_le16(sizeof(u8));
		pwr_ct->constraint = bss_cfg->power_constraint;
		cmd_size += sizeof(*pwr_ct);
		tlv += sizeof(*pwr_ct);
	}

	if (bss_cfg->ps_sta_ao_timer) {
		ps_ao_timer = (struct host_cmd_tlv_ageout_timer *)tlv;
		ps_ao_timer->header.type =
				cpu_to_le16(TLV_TYPE_UAP_PS_AO_TIMER);
		ps_ao_timer->header.len = cpu_to_le16(sizeof(*ps_ao_timer) -
				sizeof(struct mwifiex_ie_types_header));
		ps_ao_timer->sta_ao_timer =
					cpu_to_le32(bss_cfg->ps_sta_ao_timer);
		cmd_size += sizeof(*ps_ao_timer);
		tlv += sizeof(*ps_ao_timer);
	}

	*param_size = cmd_size;

	return 0;
}