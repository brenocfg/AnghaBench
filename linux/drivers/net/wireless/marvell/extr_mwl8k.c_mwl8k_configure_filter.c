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
typedef  char u8 ;
typedef  scalar_t__ u64 ;
struct mwl8k_vif {TYPE_2__* vif; } ;
struct mwl8k_priv {int sniffer_enabled; scalar_t__ ap_fw; } ;
struct mwl8k_cmd_pkt {int dummy; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;
struct TYPE_3__ {char* bssid; } ;
struct TYPE_4__ {TYPE_1__ bss_conf; } ;

/* Variables and functions */
 unsigned int FIF_ALLMULTI ; 
 unsigned int FIF_BCN_PRBRESP_PROMISC ; 
 unsigned int FIF_CONTROL ; 
 unsigned int FIF_OTHER_BSS ; 
 struct mwl8k_cmd_pkt* __mwl8k_cmd_mac_multicast_adr (struct ieee80211_hw*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_pkt*) ; 
 int /*<<< orphan*/  mwl8k_cmd_enable_sniffer (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl8k_cmd_set_post_scan (struct ieee80211_hw*,char const*) ; 
 int /*<<< orphan*/  mwl8k_cmd_set_pre_scan (struct ieee80211_hw*) ; 
 scalar_t__ mwl8k_configure_filter_sniffer (struct ieee80211_hw*,unsigned int,unsigned int*) ; 
 struct mwl8k_vif* mwl8k_first_vif (struct mwl8k_priv*) ; 
 scalar_t__ mwl8k_fw_lock (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mwl8k_fw_unlock (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mwl8k_post_cmd (struct ieee80211_hw*,struct mwl8k_cmd_pkt*) ; 

__attribute__((used)) static void mwl8k_configure_filter(struct ieee80211_hw *hw,
				   unsigned int changed_flags,
				   unsigned int *total_flags,
				   u64 multicast)
{
	struct mwl8k_priv *priv = hw->priv;
	struct mwl8k_cmd_pkt *cmd = (void *)(unsigned long)multicast;

	/*
	 * AP firmware doesn't allow fine-grained control over
	 * the receive filter.
	 */
	if (priv->ap_fw) {
		*total_flags &= FIF_ALLMULTI | FIF_BCN_PRBRESP_PROMISC;
		kfree(cmd);
		return;
	}

	/*
	 * Enable hardware sniffer mode if FIF_CONTROL or
	 * FIF_OTHER_BSS is requested.
	 */
	if (*total_flags & (FIF_CONTROL | FIF_OTHER_BSS) &&
	    mwl8k_configure_filter_sniffer(hw, changed_flags, total_flags)) {
		kfree(cmd);
		return;
	}

	/* Clear unsupported feature flags */
	*total_flags &= FIF_ALLMULTI | FIF_BCN_PRBRESP_PROMISC;

	if (mwl8k_fw_lock(hw)) {
		kfree(cmd);
		return;
	}

	if (priv->sniffer_enabled) {
		mwl8k_cmd_enable_sniffer(hw, 0);
		priv->sniffer_enabled = false;
	}

	if (changed_flags & FIF_BCN_PRBRESP_PROMISC) {
		if (*total_flags & FIF_BCN_PRBRESP_PROMISC) {
			/*
			 * Disable the BSS filter.
			 */
			mwl8k_cmd_set_pre_scan(hw);
		} else {
			struct mwl8k_vif *mwl8k_vif;
			const u8 *bssid;

			/*
			 * Enable the BSS filter.
			 *
			 * If there is an active STA interface, use that
			 * interface's BSSID, otherwise use a dummy one
			 * (where the OUI part needs to be nonzero for
			 * the BSSID to be accepted by POST_SCAN).
			 */
			mwl8k_vif = mwl8k_first_vif(priv);
			if (mwl8k_vif != NULL)
				bssid = mwl8k_vif->vif->bss_conf.bssid;
			else
				bssid = "\x01\x00\x00\x00\x00\x00";

			mwl8k_cmd_set_post_scan(hw, bssid);
		}
	}

	/*
	 * If FIF_ALLMULTI is being requested, throw away the command
	 * packet that ->prepare_multicast() built and replace it with
	 * a command packet that enables reception of all multicast
	 * packets.
	 */
	if (*total_flags & FIF_ALLMULTI) {
		kfree(cmd);
		cmd = __mwl8k_cmd_mac_multicast_adr(hw, 1, NULL);
	}

	if (cmd != NULL) {
		mwl8k_post_cmd(hw, cmd);
		kfree(cmd);
	}

	mwl8k_fw_unlock(hw);
}