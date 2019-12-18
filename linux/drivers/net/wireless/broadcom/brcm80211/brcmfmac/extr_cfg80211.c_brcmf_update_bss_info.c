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
typedef  int /*<<< orphan*/  u32 ;
struct brcmf_tlv {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {int /*<<< orphan*/  vif; } ;
struct brcmf_cfg80211_info {scalar_t__ extra_buf; struct brcmf_pub* pub; } ;
struct brcmf_bss_info_le {int /*<<< orphan*/  ie_length; int /*<<< orphan*/  ie_offset; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_GET_BSS_INFO ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  WLAN_EID_TIM ; 
 int /*<<< orphan*/  WL_EXTRA_BUF_MAX ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ brcmf_fil_cmd_data_get (struct brcmf_if*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ brcmf_fil_iovar_int_get (struct brcmf_if*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ brcmf_inform_single_bss (struct brcmf_cfg80211_info*,struct brcmf_bss_info_le*) ; 
 scalar_t__ brcmf_is_ibssmode (int /*<<< orphan*/ ) ; 
 struct brcmf_tlv* brcmf_parse_tlvs (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 brcmf_update_bss_info(struct brcmf_cfg80211_info *cfg,
				 struct brcmf_if *ifp)
{
	struct brcmf_pub *drvr = cfg->pub;
	struct brcmf_bss_info_le *bi;
	const struct brcmf_tlv *tim;
	size_t ie_len;
	u8 *ie;
	s32 err = 0;

	brcmf_dbg(TRACE, "Enter\n");
	if (brcmf_is_ibssmode(ifp->vif))
		return err;

	*(__le32 *)cfg->extra_buf = cpu_to_le32(WL_EXTRA_BUF_MAX);
	err = brcmf_fil_cmd_data_get(ifp, BRCMF_C_GET_BSS_INFO,
				     cfg->extra_buf, WL_EXTRA_BUF_MAX);
	if (err) {
		bphy_err(drvr, "Could not get bss info %d\n", err);
		goto update_bss_info_out;
	}

	bi = (struct brcmf_bss_info_le *)(cfg->extra_buf + 4);
	err = brcmf_inform_single_bss(cfg, bi);
	if (err)
		goto update_bss_info_out;

	ie = ((u8 *)bi) + le16_to_cpu(bi->ie_offset);
	ie_len = le32_to_cpu(bi->ie_length);

	tim = brcmf_parse_tlvs(ie, ie_len, WLAN_EID_TIM);
	if (!tim) {
		/*
		* active scan was done so we could not get dtim
		* information out of probe response.
		* so we speficially query dtim information to dongle.
		*/
		u32 var;
		err = brcmf_fil_iovar_int_get(ifp, "dtim_assoc", &var);
		if (err) {
			bphy_err(drvr, "wl dtim_assoc failed (%d)\n", err);
			goto update_bss_info_out;
		}
	}

update_bss_info_out:
	brcmf_dbg(TRACE, "Exit");
	return err;
}