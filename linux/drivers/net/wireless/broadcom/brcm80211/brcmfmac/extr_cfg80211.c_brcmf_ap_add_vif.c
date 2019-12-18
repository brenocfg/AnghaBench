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
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct vif_params {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {TYPE_1__* vif; TYPE_2__* ndev; } ;
struct brcmf_cfg80211_vif {struct brcmf_if* ifp; } ;
struct brcmf_cfg80211_info {struct brcmf_pub* pub; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct wireless_dev wdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_E_IF_ADD ; 
 int /*<<< orphan*/  BRCMF_VIF_EVENT_TIMEOUT ; 
 int EBUSY ; 
 int EIO ; 
 int ENOENT ; 
 struct wireless_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ IS_ERR (struct brcmf_cfg80211_vif*) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*) ; 
 struct brcmf_cfg80211_vif* brcmf_alloc_vif (struct brcmf_cfg80211_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_cfg80211_arm_vif_event (struct brcmf_cfg80211_info*,struct brcmf_cfg80211_vif*) ; 
 int brcmf_cfg80211_request_ap_if (struct brcmf_if*) ; 
 scalar_t__ brcmf_cfg80211_vif_event_armed (struct brcmf_cfg80211_info*) ; 
 int brcmf_cfg80211_wait_vif_event (struct brcmf_cfg80211_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  brcmf_free_vif (struct brcmf_cfg80211_vif*) ; 
 int brcmf_net_attach (struct brcmf_if*,int) ; 
 int /*<<< orphan*/  cfg_to_ndev (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  free_netdev (TYPE_2__*) ; 
 struct brcmf_if* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 
 struct brcmf_cfg80211_info* wiphy_to_cfg (struct wiphy*) ; 

__attribute__((used)) static
struct wireless_dev *brcmf_ap_add_vif(struct wiphy *wiphy, const char *name,
				      struct vif_params *params)
{
	struct brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	struct brcmf_if *ifp = netdev_priv(cfg_to_ndev(cfg));
	struct brcmf_pub *drvr = cfg->pub;
	struct brcmf_cfg80211_vif *vif;
	int err;

	if (brcmf_cfg80211_vif_event_armed(cfg))
		return ERR_PTR(-EBUSY);

	brcmf_dbg(INFO, "Adding vif \"%s\"\n", name);

	vif = brcmf_alloc_vif(cfg, NL80211_IFTYPE_AP);
	if (IS_ERR(vif))
		return (struct wireless_dev *)vif;

	brcmf_cfg80211_arm_vif_event(cfg, vif);

	err = brcmf_cfg80211_request_ap_if(ifp);
	if (err) {
		brcmf_cfg80211_arm_vif_event(cfg, NULL);
		goto fail;
	}

	/* wait for firmware event */
	err = brcmf_cfg80211_wait_vif_event(cfg, BRCMF_E_IF_ADD,
					    BRCMF_VIF_EVENT_TIMEOUT);
	brcmf_cfg80211_arm_vif_event(cfg, NULL);
	if (!err) {
		bphy_err(drvr, "timeout occurred\n");
		err = -EIO;
		goto fail;
	}

	/* interface created in firmware */
	ifp = vif->ifp;
	if (!ifp) {
		bphy_err(drvr, "no if pointer provided\n");
		err = -ENOENT;
		goto fail;
	}

	strncpy(ifp->ndev->name, name, sizeof(ifp->ndev->name) - 1);
	err = brcmf_net_attach(ifp, true);
	if (err) {
		bphy_err(drvr, "Registering netdevice failed\n");
		free_netdev(ifp->ndev);
		goto fail;
	}

	return &ifp->vif->wdev;

fail:
	brcmf_free_vif(vif);
	return ERR_PTR(err);
}