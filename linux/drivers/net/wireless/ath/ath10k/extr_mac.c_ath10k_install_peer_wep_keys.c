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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ath10k_vif {int def_wep_key_idx; int /*<<< orphan*/  vdev_id; struct ath10k* ar; TYPE_1__* vif; int /*<<< orphan*/ ** wep_keys; } ;
struct ath10k_peer {int /*<<< orphan*/ ** keys; } ;
struct TYPE_6__ {TYPE_2__* vdev_param; } ;
struct ath10k {TYPE_3__ wmi; int /*<<< orphan*/  data_lock; int /*<<< orphan*/  conf_mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  def_keyid; } ;
struct TYPE_4__ {int type; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int EINVAL ; 
 int ENOENT ; 
#define  NL80211_IFTYPE_ADHOC 129 
#define  NL80211_IFTYPE_AP 128 
 int NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  SET_KEY ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WMI_KEY_GROUP ; 
 int /*<<< orphan*/  WMI_KEY_PAIRWISE ; 
 int /*<<< orphan*/  WMI_KEY_TX_USAGE ; 
 int ath10k_install_key (struct ath10k_vif*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct ath10k_peer* ath10k_peer_find (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 int ath10k_wmi_vdev_set_param (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_install_peer_wep_keys(struct ath10k_vif *arvif,
					const u8 *addr)
{
	struct ath10k *ar = arvif->ar;
	struct ath10k_peer *peer;
	int ret;
	int i;
	u32 flags;

	lockdep_assert_held(&ar->conf_mutex);

	if (WARN_ON(arvif->vif->type != NL80211_IFTYPE_AP &&
		    arvif->vif->type != NL80211_IFTYPE_ADHOC &&
		    arvif->vif->type != NL80211_IFTYPE_MESH_POINT))
		return -EINVAL;

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find(ar, arvif->vdev_id, addr);
	spin_unlock_bh(&ar->data_lock);

	if (!peer)
		return -ENOENT;

	for (i = 0; i < ARRAY_SIZE(arvif->wep_keys); i++) {
		if (arvif->wep_keys[i] == NULL)
			continue;

		switch (arvif->vif->type) {
		case NL80211_IFTYPE_AP:
			flags = WMI_KEY_PAIRWISE;

			if (arvif->def_wep_key_idx == i)
				flags |= WMI_KEY_TX_USAGE;

			ret = ath10k_install_key(arvif, arvif->wep_keys[i],
						 SET_KEY, addr, flags);
			if (ret < 0)
				return ret;
			break;
		case NL80211_IFTYPE_ADHOC:
			ret = ath10k_install_key(arvif, arvif->wep_keys[i],
						 SET_KEY, addr,
						 WMI_KEY_PAIRWISE);
			if (ret < 0)
				return ret;

			ret = ath10k_install_key(arvif, arvif->wep_keys[i],
						 SET_KEY, addr, WMI_KEY_GROUP);
			if (ret < 0)
				return ret;
			break;
		default:
			WARN_ON(1);
			return -EINVAL;
		}

		spin_lock_bh(&ar->data_lock);
		peer->keys[i] = arvif->wep_keys[i];
		spin_unlock_bh(&ar->data_lock);
	}

	/* In some cases (notably with static WEP IBSS with multiple keys)
	 * multicast Tx becomes broken. Both pairwise and groupwise keys are
	 * installed already. Using WMI_KEY_TX_USAGE in different combinations
	 * didn't seem help. Using def_keyid vdev parameter seems to be
	 * effective so use that.
	 *
	 * FIXME: Revisit. Perhaps this can be done in a less hacky way.
	 */
	if (arvif->vif->type != NL80211_IFTYPE_ADHOC)
		return 0;

	if (arvif->def_wep_key_idx == -1)
		return 0;

	ret = ath10k_wmi_vdev_set_param(arvif->ar,
					arvif->vdev_id,
					arvif->ar->wmi.vdev_param->def_keyid,
					arvif->def_wep_key_idx);
	if (ret) {
		ath10k_warn(ar, "failed to re-set def wpa key idxon vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	return 0;
}