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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  rx_mac_timestamp; } ;
struct wmi_mgmt_rx_ev_arg {TYPE_1__ ext_info; int /*<<< orphan*/  rate; int /*<<< orphan*/  phy_mode; int /*<<< orphan*/  snr; int /*<<< orphan*/  status; int /*<<< orphan*/  channel; } ;
struct sk_buff {size_t len; scalar_t__ data; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_rx_status {int flag; size_t band; int signal; int rate_idx; struct sk_buff* freq; int /*<<< orphan*/  mactime; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_4__ {struct ieee80211_supported_band* sbands; } ;
struct ath10k {int /*<<< orphan*/  hw; TYPE_2__ mac; int /*<<< orphan*/  dev_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_CAC_RUNNING ; 
 int /*<<< orphan*/  ATH10K_DBG_MGMT ; 
 int ATH10K_DEFAULT_NOISE_FLOOR ; 
 int ATH10K_MAX_5G_CHAN ; 
 int IEEE80211_FCTL_FTYPE ; 
 int IEEE80211_FCTL_PROTECTED ; 
 int IEEE80211_FCTL_STYPE ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int MODE_11B ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int RX_FLAG_DECRYPTED ; 
 int RX_FLAG_IV_STRIPPED ; 
 int RX_FLAG_MACTIME_END ; 
 int RX_FLAG_MMIC_ERROR ; 
 int RX_FLAG_MMIC_STRIPPED ; 
 int RX_FLAG_SKIP_MONITOR ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int WMI_RX_STATUS_ERR_CRC ; 
 int WMI_RX_STATUS_ERR_DECRYPT ; 
 int WMI_RX_STATUS_ERR_KEY_CACHE_MISS ; 
 int WMI_RX_STATUS_ERR_MIC ; 
 int WMI_RX_STATUS_EXT_INFO ; 
 int /*<<< orphan*/  __cpu_to_le16 (int) ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,...) ; 
 int ath10k_mac_bitrate_to_idx (struct ieee80211_supported_band*,int) ; 
 int /*<<< orphan*/  ath10k_mac_handle_beacon (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  ath10k_wmi_handle_wep_reauth (struct ath10k*,struct sk_buff*,struct ieee80211_rx_status*) ; 
 int ath10k_wmi_pull_mgmt_rx (struct ath10k*,struct sk_buff*,struct wmi_mgmt_rx_ev_arg*) ; 
 scalar_t__ ath10k_wmi_rx_is_decrypted (struct ath10k*,struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* ieee80211_channel_to_frequency (int,size_t) ; 
 int /*<<< orphan*/  ieee80211_is_action (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_deauth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_disassoc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_rx_ni (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_rx_status*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ath10k_wmi_event_mgmt_rx(struct ath10k *ar, struct sk_buff *skb)
{
	struct wmi_mgmt_rx_ev_arg arg = {};
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	struct ieee80211_hdr *hdr;
	struct ieee80211_supported_band *sband;
	u32 rx_status;
	u32 channel;
	u32 phy_mode;
	u32 snr;
	u32 rate;
	u16 fc;
	int ret;

	ret = ath10k_wmi_pull_mgmt_rx(ar, skb, &arg);
	if (ret) {
		ath10k_warn(ar, "failed to parse mgmt rx event: %d\n", ret);
		dev_kfree_skb(skb);
		return ret;
	}

	channel = __le32_to_cpu(arg.channel);
	rx_status = __le32_to_cpu(arg.status);
	snr = __le32_to_cpu(arg.snr);
	phy_mode = __le32_to_cpu(arg.phy_mode);
	rate = __le32_to_cpu(arg.rate);

	memset(status, 0, sizeof(*status));

	ath10k_dbg(ar, ATH10K_DBG_MGMT,
		   "event mgmt rx status %08x\n", rx_status);

	if ((test_bit(ATH10K_CAC_RUNNING, &ar->dev_flags)) ||
	    (rx_status & (WMI_RX_STATUS_ERR_DECRYPT |
	    WMI_RX_STATUS_ERR_KEY_CACHE_MISS | WMI_RX_STATUS_ERR_CRC))) {
		dev_kfree_skb(skb);
		return 0;
	}

	if (rx_status & WMI_RX_STATUS_ERR_MIC)
		status->flag |= RX_FLAG_MMIC_ERROR;

	if (rx_status & WMI_RX_STATUS_EXT_INFO) {
		status->mactime =
			__le64_to_cpu(arg.ext_info.rx_mac_timestamp);
		status->flag |= RX_FLAG_MACTIME_END;
	}
	/* Hardware can Rx CCK rates on 5GHz. In that case phy_mode is set to
	 * MODE_11B. This means phy_mode is not a reliable source for the band
	 * of mgmt rx.
	 */
	if (channel >= 1 && channel <= 14) {
		status->band = NL80211_BAND_2GHZ;
	} else if (channel >= 36 && channel <= ATH10K_MAX_5G_CHAN) {
		status->band = NL80211_BAND_5GHZ;
	} else {
		/* Shouldn't happen unless list of advertised channels to
		 * mac80211 has been changed.
		 */
		WARN_ON_ONCE(1);
		dev_kfree_skb(skb);
		return 0;
	}

	if (phy_mode == MODE_11B && status->band == NL80211_BAND_5GHZ)
		ath10k_dbg(ar, ATH10K_DBG_MGMT, "wmi mgmt rx 11b (CCK) on 5GHz\n");

	sband = &ar->mac.sbands[status->band];

	status->freq = ieee80211_channel_to_frequency(channel, status->band);
	status->signal = snr + ATH10K_DEFAULT_NOISE_FLOOR;
	status->rate_idx = ath10k_mac_bitrate_to_idx(sband, rate / 100);

	hdr = (struct ieee80211_hdr *)skb->data;
	fc = le16_to_cpu(hdr->frame_control);

	/* Firmware is guaranteed to report all essential management frames via
	 * WMI while it can deliver some extra via HTT. Since there can be
	 * duplicates split the reporting wrt monitor/sniffing.
	 */
	status->flag |= RX_FLAG_SKIP_MONITOR;

	ath10k_wmi_handle_wep_reauth(ar, skb, status);

	if (ath10k_wmi_rx_is_decrypted(ar, hdr)) {
		status->flag |= RX_FLAG_DECRYPTED;

		if (!ieee80211_is_action(hdr->frame_control) &&
		    !ieee80211_is_deauth(hdr->frame_control) &&
		    !ieee80211_is_disassoc(hdr->frame_control)) {
			status->flag |= RX_FLAG_IV_STRIPPED |
					RX_FLAG_MMIC_STRIPPED;
			hdr->frame_control = __cpu_to_le16(fc &
					~IEEE80211_FCTL_PROTECTED);
		}
	}

	if (ieee80211_is_beacon(hdr->frame_control))
		ath10k_mac_handle_beacon(ar, skb);

	ath10k_dbg(ar, ATH10K_DBG_MGMT,
		   "event mgmt rx skb %pK len %d ftype %02x stype %02x\n",
		   skb, skb->len,
		   fc & IEEE80211_FCTL_FTYPE, fc & IEEE80211_FCTL_STYPE);

	ath10k_dbg(ar, ATH10K_DBG_MGMT,
		   "event mgmt rx freq %d band %d snr %d, rate_idx %d\n",
		   status->freq, status->band, status->signal,
		   status->rate_idx);

	ieee80211_rx_ni(ar->hw, skb);

	return 0;
}