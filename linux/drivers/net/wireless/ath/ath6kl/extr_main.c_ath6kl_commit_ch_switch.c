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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  ch; } ;
struct ath6kl_vif {int nw_type; TYPE_1__ profile; int /*<<< orphan*/  fw_vif_idx; int /*<<< orphan*/  rsn_capab; struct ath6kl* ar; } ;
struct ath6kl {int /*<<< orphan*/  wmi; int /*<<< orphan*/  fw_capabilities; } ;

/* Variables and functions */
#define  AP_NETWORK 128 
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_RSN_CAP_OVERRIDE ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  WLAN_EID_RSN ; 
 int /*<<< orphan*/  WMI_RSN_IE_CAPB ; 
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 
 int ath6kl_wmi_ap_profile_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ath6kl_wmi_set_ie_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_commit_ch_switch(struct ath6kl_vif *vif, u16 channel)
{
	struct ath6kl *ar = vif->ar;

	vif->profile.ch = cpu_to_le16(channel);

	switch (vif->nw_type) {
	case AP_NETWORK:
		/*
		 * reconfigure any saved RSN IE capabilites in the beacon /
		 * probe response to stay in sync with the supplicant.
		 */
		if (vif->rsn_capab &&
		    test_bit(ATH6KL_FW_CAPABILITY_RSN_CAP_OVERRIDE,
			     ar->fw_capabilities))
			ath6kl_wmi_set_ie_cmd(ar->wmi, vif->fw_vif_idx,
					      WLAN_EID_RSN, WMI_RSN_IE_CAPB,
					      (const u8 *) &vif->rsn_capab,
					      sizeof(vif->rsn_capab));

		return ath6kl_wmi_ap_profile_commit(ar->wmi, vif->fw_vif_idx,
						    &vif->profile);
	default:
		ath6kl_err("won't switch channels nw_type=%d\n", vif->nw_type);
		return -ENOTSUPP;
	}
}