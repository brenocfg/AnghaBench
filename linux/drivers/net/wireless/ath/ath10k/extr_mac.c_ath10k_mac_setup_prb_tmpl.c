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
struct sk_buff {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ath10k_vif {scalar_t__ vdev_type; int /*<<< orphan*/  vdev_id; struct ieee80211_vif* vif; struct ath10k* ar; } ;
struct TYPE_2__ {int /*<<< orphan*/  svc_map; } ;
struct ath10k {TYPE_1__ wmi; struct ieee80211_hw* hw; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  WMI_SERVICE_BEACON_OFFLOAD ; 
 scalar_t__ WMI_VDEV_TYPE_AP ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 int ath10k_wmi_prb_tmpl (struct ath10k*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* ieee80211_proberesp_get (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 scalar_t__ ieee80211_vif_is_mesh (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_mac_setup_prb_tmpl(struct ath10k_vif *arvif)
{
	struct ath10k *ar = arvif->ar;
	struct ieee80211_hw *hw = ar->hw;
	struct ieee80211_vif *vif = arvif->vif;
	struct sk_buff *prb;
	int ret;

	if (!test_bit(WMI_SERVICE_BEACON_OFFLOAD, ar->wmi.svc_map))
		return 0;

	if (arvif->vdev_type != WMI_VDEV_TYPE_AP)
		return 0;

	 /* For mesh, probe response and beacon share the same template */
	if (ieee80211_vif_is_mesh(vif))
		return 0;

	prb = ieee80211_proberesp_get(hw, vif);
	if (!prb) {
		ath10k_warn(ar, "failed to get probe resp template from mac80211\n");
		return -EPERM;
	}

	ret = ath10k_wmi_prb_tmpl(ar, arvif->vdev_id, prb);
	kfree_skb(prb);

	if (ret) {
		ath10k_warn(ar, "failed to submit probe resp template command: %d\n",
			    ret);
		return ret;
	}

	return 0;
}