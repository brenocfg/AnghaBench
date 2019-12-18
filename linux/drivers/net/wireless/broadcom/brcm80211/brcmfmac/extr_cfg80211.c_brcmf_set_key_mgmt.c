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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int* akm_suites; int cipher_group; int /*<<< orphan*/  n_akm_suites; } ;
struct cfg80211_connect_params {int /*<<< orphan*/  ie_len; scalar_t__ ie; TYPE_2__ crypto; int /*<<< orphan*/  want_1x; } ;
struct brcmf_tlv {scalar_t__ len; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {struct brcmf_pub* drvr; TYPE_1__* vif; } ;
struct brcmf_cfg80211_profile {scalar_t__ use_fwsup; } ;
typedef  int s32 ;
struct TYPE_3__ {struct brcmf_cfg80211_profile profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_FEAT_MFP ; 
 scalar_t__ BRCMF_MFP_CAPABLE ; 
 scalar_t__ BRCMF_MFP_NONE ; 
 scalar_t__ BRCMF_MFP_REQUIRED ; 
 scalar_t__ BRCMF_PROFILE_FWSUP_1X ; 
 scalar_t__ BRCMF_PROFILE_FWSUP_NONE ; 
 int /*<<< orphan*/  CONN ; 
 int EINVAL ; 
 int /*<<< orphan*/  INFO ; 
 int RSN_CAP_MFPC_MASK ; 
 int RSN_CAP_MFPR_MASK ; 
 scalar_t__ TLV_HDR_LEN ; 
#define  WLAN_AKM_SUITE_8021X 133 
#define  WLAN_AKM_SUITE_8021X_SHA256 132 
#define  WLAN_AKM_SUITE_FT_8021X 131 
#define  WLAN_AKM_SUITE_FT_PSK 130 
#define  WLAN_AKM_SUITE_PSK 129 
#define  WLAN_AKM_SUITE_PSK_SHA256 128 
 int /*<<< orphan*/  WLAN_EID_RSN ; 
 int WPA2_AUTH_1X_SHA256 ; 
 int WPA2_AUTH_FT ; 
 int WPA2_AUTH_PSK ; 
 int WPA2_AUTH_PSK_SHA256 ; 
 int WPA2_AUTH_UNSPECIFIED ; 
 int WPA_AUTH_PSK ; 
 int WPA_AUTH_UNSPECIFIED ; 
 int WPA_IE_MIN_OUI_LEN ; 
 scalar_t__ WPA_IE_SUITE_COUNT_LEN ; 
 scalar_t__ WPA_IE_VERSION_LEN ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_feat_is_enabled (struct brcmf_if*,int /*<<< orphan*/ ) ; 
 int brcmf_fil_bsscfg_int_get (struct brcmf_if*,char*,int*) ; 
 int brcmf_fil_bsscfg_int_set (struct brcmf_if*,char*,int) ; 
 struct brcmf_tlv* brcmf_parse_tlvs (int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 

__attribute__((used)) static s32
brcmf_set_key_mgmt(struct net_device *ndev, struct cfg80211_connect_params *sme)
{
	struct brcmf_if *ifp = netdev_priv(ndev);
	struct brcmf_cfg80211_profile *profile = &ifp->vif->profile;
	struct brcmf_pub *drvr = ifp->drvr;
	s32 val;
	s32 err;
	const struct brcmf_tlv *rsn_ie;
	const u8 *ie;
	u32 ie_len;
	u32 offset;
	u16 rsn_cap;
	u32 mfp;
	u16 count;

	profile->use_fwsup = BRCMF_PROFILE_FWSUP_NONE;

	if (!sme->crypto.n_akm_suites)
		return 0;

	err = brcmf_fil_bsscfg_int_get(netdev_priv(ndev), "wpa_auth", &val);
	if (err) {
		bphy_err(drvr, "could not get wpa_auth (%d)\n", err);
		return err;
	}
	if (val & (WPA_AUTH_PSK | WPA_AUTH_UNSPECIFIED)) {
		switch (sme->crypto.akm_suites[0]) {
		case WLAN_AKM_SUITE_8021X:
			val = WPA_AUTH_UNSPECIFIED;
			if (sme->want_1x)
				profile->use_fwsup = BRCMF_PROFILE_FWSUP_1X;
			break;
		case WLAN_AKM_SUITE_PSK:
			val = WPA_AUTH_PSK;
			break;
		default:
			bphy_err(drvr, "invalid cipher group (%d)\n",
				 sme->crypto.cipher_group);
			return -EINVAL;
		}
	} else if (val & (WPA2_AUTH_PSK | WPA2_AUTH_UNSPECIFIED)) {
		switch (sme->crypto.akm_suites[0]) {
		case WLAN_AKM_SUITE_8021X:
			val = WPA2_AUTH_UNSPECIFIED;
			if (sme->want_1x)
				profile->use_fwsup = BRCMF_PROFILE_FWSUP_1X;
			break;
		case WLAN_AKM_SUITE_8021X_SHA256:
			val = WPA2_AUTH_1X_SHA256;
			if (sme->want_1x)
				profile->use_fwsup = BRCMF_PROFILE_FWSUP_1X;
			break;
		case WLAN_AKM_SUITE_PSK_SHA256:
			val = WPA2_AUTH_PSK_SHA256;
			break;
		case WLAN_AKM_SUITE_PSK:
			val = WPA2_AUTH_PSK;
			break;
		case WLAN_AKM_SUITE_FT_8021X:
			val = WPA2_AUTH_UNSPECIFIED | WPA2_AUTH_FT;
			if (sme->want_1x)
				profile->use_fwsup = BRCMF_PROFILE_FWSUP_1X;
			break;
		case WLAN_AKM_SUITE_FT_PSK:
			val = WPA2_AUTH_PSK | WPA2_AUTH_FT;
			break;
		default:
			bphy_err(drvr, "invalid cipher group (%d)\n",
				 sme->crypto.cipher_group);
			return -EINVAL;
		}
	}

	if (profile->use_fwsup == BRCMF_PROFILE_FWSUP_1X)
		brcmf_dbg(INFO, "using 1X offload\n");

	if (!brcmf_feat_is_enabled(ifp, BRCMF_FEAT_MFP))
		goto skip_mfp_config;
	/* The MFP mode (1 or 2) needs to be determined, parse IEs. The
	 * IE will not be verified, just a quick search for MFP config
	 */
	rsn_ie = brcmf_parse_tlvs((const u8 *)sme->ie, sme->ie_len,
				  WLAN_EID_RSN);
	if (!rsn_ie)
		goto skip_mfp_config;
	ie = (const u8 *)rsn_ie;
	ie_len = rsn_ie->len + TLV_HDR_LEN;
	/* Skip unicast suite */
	offset = TLV_HDR_LEN + WPA_IE_VERSION_LEN + WPA_IE_MIN_OUI_LEN;
	if (offset + WPA_IE_SUITE_COUNT_LEN >= ie_len)
		goto skip_mfp_config;
	/* Skip multicast suite */
	count = ie[offset] + (ie[offset + 1] << 8);
	offset += WPA_IE_SUITE_COUNT_LEN + (count * WPA_IE_MIN_OUI_LEN);
	if (offset + WPA_IE_SUITE_COUNT_LEN >= ie_len)
		goto skip_mfp_config;
	/* Skip auth key management suite(s) */
	count = ie[offset] + (ie[offset + 1] << 8);
	offset += WPA_IE_SUITE_COUNT_LEN + (count * WPA_IE_MIN_OUI_LEN);
	if (offset + WPA_IE_SUITE_COUNT_LEN > ie_len)
		goto skip_mfp_config;
	/* Ready to read capabilities */
	mfp = BRCMF_MFP_NONE;
	rsn_cap = ie[offset] + (ie[offset + 1] << 8);
	if (rsn_cap & RSN_CAP_MFPR_MASK)
		mfp = BRCMF_MFP_REQUIRED;
	else if (rsn_cap & RSN_CAP_MFPC_MASK)
		mfp = BRCMF_MFP_CAPABLE;
	brcmf_fil_bsscfg_int_set(netdev_priv(ndev), "mfp", mfp);

skip_mfp_config:
	brcmf_dbg(CONN, "setting wpa_auth to %d\n", val);
	err = brcmf_fil_bsscfg_int_set(netdev_priv(ndev), "wpa_auth", val);
	if (err) {
		bphy_err(drvr, "could not set wpa_auth (%d)\n", err);
		return err;
	}

	return err;
}