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
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct brcmf_scb_val_le {int /*<<< orphan*/  val; int /*<<< orphan*/  ea; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {TYPE_1__* vif; } ;
struct brcmf_cfg80211_profile {int /*<<< orphan*/  bssid; } ;
struct brcmf_cfg80211_info {struct brcmf_pub* pub; } ;
typedef  int /*<<< orphan*/  scbval ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {int /*<<< orphan*/  sme_state; struct brcmf_cfg80211_profile profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_DISASSOC ; 
 int /*<<< orphan*/  BRCMF_VIF_STATUS_CONNECTED ; 
 int /*<<< orphan*/  BRCMF_VIF_STATUS_CONNECTING ; 
 scalar_t__ EIO ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ brcmf_fil_cmd_data_set (struct brcmf_if*,int /*<<< orphan*/ ,struct brcmf_scb_val_le*,int) ; 
 int /*<<< orphan*/  cfg80211_disconnected (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_vif_up (TYPE_1__*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 
 struct brcmf_cfg80211_info* wiphy_to_cfg (struct wiphy*) ; 

__attribute__((used)) static s32
brcmf_cfg80211_disconnect(struct wiphy *wiphy, struct net_device *ndev,
		       u16 reason_code)
{
	struct brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	struct brcmf_if *ifp = netdev_priv(ndev);
	struct brcmf_cfg80211_profile *profile = &ifp->vif->profile;
	struct brcmf_pub *drvr = cfg->pub;
	struct brcmf_scb_val_le scbval;
	s32 err = 0;

	brcmf_dbg(TRACE, "Enter. Reason code = %d\n", reason_code);
	if (!check_vif_up(ifp->vif))
		return -EIO;

	clear_bit(BRCMF_VIF_STATUS_CONNECTED, &ifp->vif->sme_state);
	clear_bit(BRCMF_VIF_STATUS_CONNECTING, &ifp->vif->sme_state);
	cfg80211_disconnected(ndev, reason_code, NULL, 0, true, GFP_KERNEL);

	memcpy(&scbval.ea, &profile->bssid, ETH_ALEN);
	scbval.val = cpu_to_le32(reason_code);
	err = brcmf_fil_cmd_data_set(ifp, BRCMF_C_DISASSOC,
				     &scbval, sizeof(scbval));
	if (err)
		bphy_err(drvr, "error (%d)\n", err);

	brcmf_dbg(TRACE, "Exit\n");
	return err;
}