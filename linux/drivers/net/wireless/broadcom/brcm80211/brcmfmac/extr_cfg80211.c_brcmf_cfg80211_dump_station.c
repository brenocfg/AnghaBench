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
struct wiphy {int dummy; } ;
struct station_info {int dummy; } ;
struct net_device {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mac; scalar_t__ count; } ;
struct brcmf_cfg80211_info {TYPE_1__ assoclist; struct brcmf_pub* pub; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_GET_ASSOCLIST ; 
 int /*<<< orphan*/  BRCMF_MAX_ASSOCLIST ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,scalar_t__) ; 
 int brcmf_cfg80211_get_station (struct wiphy*,struct net_device*,int /*<<< orphan*/ *,struct station_info*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ brcmf_fil_cmd_data_get (struct brcmf_if*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 
 struct brcmf_cfg80211_info* wiphy_to_cfg (struct wiphy*) ; 

__attribute__((used)) static int
brcmf_cfg80211_dump_station(struct wiphy *wiphy, struct net_device *ndev,
			    int idx, u8 *mac, struct station_info *sinfo)
{
	struct brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	struct brcmf_if *ifp = netdev_priv(ndev);
	struct brcmf_pub *drvr = cfg->pub;
	s32 err;

	brcmf_dbg(TRACE, "Enter, idx %d\n", idx);

	if (idx == 0) {
		cfg->assoclist.count = cpu_to_le32(BRCMF_MAX_ASSOCLIST);
		err = brcmf_fil_cmd_data_get(ifp, BRCMF_C_GET_ASSOCLIST,
					     &cfg->assoclist,
					     sizeof(cfg->assoclist));
		if (err) {
			bphy_err(drvr, "BRCMF_C_GET_ASSOCLIST unsupported, err=%d\n",
				 err);
			cfg->assoclist.count = 0;
			return -EOPNOTSUPP;
		}
	}
	if (idx < le32_to_cpu(cfg->assoclist.count)) {
		memcpy(mac, cfg->assoclist.mac[idx], ETH_ALEN);
		return brcmf_cfg80211_get_station(wiphy, ndev, mac, sinfo);
	}
	return -ENOENT;
}