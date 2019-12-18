#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_sta {scalar_t__ tdls; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ath10k_skb_cb {int flags; } ;
struct TYPE_4__ {int target_version_major; } ;
struct ath10k {int /*<<< orphan*/  dev_flags; TYPE_3__* running_fw; TYPE_1__ htt; } ;
typedef  enum ath10k_hw_txrx_mode { ____Placeholder_ath10k_hw_txrx_mode } ath10k_hw_txrx_mode ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_5__ {int /*<<< orphan*/ * fw_features; } ;
struct TYPE_6__ {TYPE_2__ fw_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FLAG_RAW_MODE ; 
 int /*<<< orphan*/  ATH10K_FW_FEATURE_HAS_WMI_MGMT_TX ; 
 int ATH10K_HW_TXRX_ETHERNET ; 
 int ATH10K_HW_TXRX_MGMT ; 
 int ATH10K_HW_TXRX_NATIVE_WIFI ; 
 int ATH10K_HW_TXRX_RAW ; 
 struct ath10k_skb_cb* ATH10K_SKB_CB (struct sk_buff*) ; 
 int ATH10K_SKB_F_RAW_TX ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 scalar_t__ ieee80211_is_data_present (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_nullfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_qos_nullfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum ath10k_hw_txrx_mode
ath10k_mac_tx_h_get_txmode(struct ath10k *ar,
			   struct ieee80211_vif *vif,
			   struct ieee80211_sta *sta,
			   struct sk_buff *skb)
{
	const struct ieee80211_hdr *hdr = (void *)skb->data;
	const struct ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(skb);
	__le16 fc = hdr->frame_control;

	if (!vif || vif->type == NL80211_IFTYPE_MONITOR)
		return ATH10K_HW_TXRX_RAW;

	if (ieee80211_is_mgmt(fc))
		return ATH10K_HW_TXRX_MGMT;

	/* Workaround:
	 *
	 * NullFunc frames are mostly used to ping if a client or AP are still
	 * reachable and responsive. This implies tx status reports must be
	 * accurate - otherwise either mac80211 or userspace (e.g. hostapd) can
	 * come to a conclusion that the other end disappeared and tear down
	 * BSS connection or it can never disconnect from BSS/client (which is
	 * the case).
	 *
	 * Firmware with HTT older than 3.0 delivers incorrect tx status for
	 * NullFunc frames to driver. However there's a HTT Mgmt Tx command
	 * which seems to deliver correct tx reports for NullFunc frames. The
	 * downside of using it is it ignores client powersave state so it can
	 * end up disconnecting sleeping clients in AP mode. It should fix STA
	 * mode though because AP don't sleep.
	 */
	if (ar->htt.target_version_major < 3 &&
	    (ieee80211_is_nullfunc(fc) || ieee80211_is_qos_nullfunc(fc)) &&
	    !test_bit(ATH10K_FW_FEATURE_HAS_WMI_MGMT_TX,
		      ar->running_fw->fw_file.fw_features))
		return ATH10K_HW_TXRX_MGMT;

	/* Workaround:
	 *
	 * Some wmi-tlv firmwares for qca6174 have broken Tx key selection for
	 * NativeWifi txmode - it selects AP key instead of peer key. It seems
	 * to work with Ethernet txmode so use it.
	 *
	 * FIXME: Check if raw mode works with TDLS.
	 */
	if (ieee80211_is_data_present(fc) && sta && sta->tdls)
		return ATH10K_HW_TXRX_ETHERNET;

	if (test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags) ||
	    skb_cb->flags & ATH10K_SKB_F_RAW_TX)
		return ATH10K_HW_TXRX_RAW;

	return ATH10K_HW_TXRX_NATIVE_WIFI;
}