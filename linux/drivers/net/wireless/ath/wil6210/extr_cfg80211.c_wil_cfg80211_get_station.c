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
struct wiphy {int dummy; } ;
struct wil6210_vif {int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int dummy; } ;
struct station_info {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 int wil_cid_fill_sinfo (struct wil6210_vif*,int,struct station_info*) ; 
 int /*<<< orphan*/  wil_cid_valid (struct wil6210_priv*,int) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int wil_find_cid (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 

__attribute__((used)) static int wil_cfg80211_get_station(struct wiphy *wiphy,
				    struct net_device *ndev,
				    const u8 *mac, struct station_info *sinfo)
{
	struct wil6210_vif *vif = ndev_to_vif(ndev);
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	int rc;

	int cid = wil_find_cid(wil, vif->mid, mac);

	wil_dbg_misc(wil, "get_station: %pM CID %d MID %d\n", mac, cid,
		     vif->mid);
	if (!wil_cid_valid(wil, cid))
		return -ENOENT;

	rc = wil_cid_fill_sinfo(vif, cid, sinfo);

	return rc;
}