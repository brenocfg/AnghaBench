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
struct ieee80211_vif {int active; int id; int enable_beacon; int type; int /*<<< orphan*/  list; int /*<<< orphan*/  addr; scalar_t__ drv_priv; int /*<<< orphan*/  p2p; int /*<<< orphan*/ * beacon; } ;
struct ieee80211_hw {struct ar9170* priv; } ;
struct carl9170_vif_info {int active; int id; int enable_beacon; int type; int /*<<< orphan*/  list; int /*<<< orphan*/  addr; scalar_t__ drv_priv; int /*<<< orphan*/  p2p; int /*<<< orphan*/ * beacon; } ;
struct TYPE_6__ {int /*<<< orphan*/  off_override; } ;
struct TYPE_4__ {scalar_t__ tx_seq_table; int /*<<< orphan*/  vif_num; } ;
struct ar9170 {int vifs; int /*<<< orphan*/  mutex; TYPE_3__ ps; TYPE_2__* vif_priv; int /*<<< orphan*/  vif_bitmap; TYPE_1__ fw; int /*<<< orphan*/  beacon_iter; int /*<<< orphan*/  vif_list; int /*<<< orphan*/  beacon_lock; } ;
struct TYPE_5__ {int id; int /*<<< orphan*/  vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 int ENOSPC ; 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MESH_POINT 129 
#define  NL80211_IFTYPE_STATION 128 
 int const NL80211_IFTYPE_WDS ; 
 int /*<<< orphan*/  PS_OFF_VIF ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bitmap_find_free_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct ieee80211_vif* carl9170_get_main_vif (struct ar9170*) ; 
 int carl9170_init_interface (struct ar9170*,struct ieee80211_vif*) ; 
 int carl9170_mod_virtual_mac (struct ar9170*,int,int /*<<< orphan*/ ) ; 
 int carl9170_write_reg (struct ar9170*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int carl9170_op_add_interface(struct ieee80211_hw *hw,
				     struct ieee80211_vif *vif)
{
	struct carl9170_vif_info *vif_priv = (void *) vif->drv_priv;
	struct ieee80211_vif *main_vif, *old_main = NULL;
	struct ar9170 *ar = hw->priv;
	int vif_id = -1, err = 0;

	mutex_lock(&ar->mutex);
	rcu_read_lock();
	if (vif_priv->active) {
		/*
		 * Skip the interface structure initialization,
		 * if the vif survived the _restart call.
		 */
		vif_id = vif_priv->id;
		vif_priv->enable_beacon = false;

		spin_lock_bh(&ar->beacon_lock);
		dev_kfree_skb_any(vif_priv->beacon);
		vif_priv->beacon = NULL;
		spin_unlock_bh(&ar->beacon_lock);

		goto init;
	}

	/* Because the AR9170 HW's MAC doesn't provide full support for
	 * multiple, independent interfaces [of different operation modes].
	 * We have to select ONE main interface [main mode of HW], but we
	 * can have multiple slaves [AKA: entry in the ACK-table].
	 *
	 * The first (from HEAD/TOP) interface in the ar->vif_list is
	 * always the main intf. All following intfs in this list
	 * are considered to be slave intfs.
	 */
	main_vif = carl9170_get_main_vif(ar);

	if (main_vif) {
		switch (main_vif->type) {
		case NL80211_IFTYPE_STATION:
			if (vif->type == NL80211_IFTYPE_STATION)
				break;

			/* P2P GO [master] use-case
			 * Because the P2P GO station is selected dynamically
			 * by all participating peers of a WIFI Direct network,
			 * the driver has be able to change the main interface
			 * operating mode on the fly.
			 */
			if (main_vif->p2p && vif->p2p &&
			    vif->type == NL80211_IFTYPE_AP) {
				old_main = main_vif;
				break;
			}

			err = -EBUSY;
			rcu_read_unlock();

			goto unlock;

		case NL80211_IFTYPE_MESH_POINT:
		case NL80211_IFTYPE_AP:
			if ((vif->type == NL80211_IFTYPE_STATION) ||
			    (vif->type == NL80211_IFTYPE_WDS) ||
			    (vif->type == NL80211_IFTYPE_AP) ||
			    (vif->type == NL80211_IFTYPE_MESH_POINT))
				break;

			err = -EBUSY;
			rcu_read_unlock();
			goto unlock;

		default:
			rcu_read_unlock();
			goto unlock;
		}
	}

	vif_id = bitmap_find_free_region(&ar->vif_bitmap, ar->fw.vif_num, 0);

	if (vif_id < 0) {
		rcu_read_unlock();

		err = -ENOSPC;
		goto unlock;
	}

	BUG_ON(ar->vif_priv[vif_id].id != vif_id);

	vif_priv->active = true;
	vif_priv->id = vif_id;
	vif_priv->enable_beacon = false;
	ar->vifs++;
	if (old_main) {
		/* We end up in here, if the main interface is being replaced.
		 * Put the new main interface at the HEAD of the list and the
		 * previous inteface will automatically become second in line.
		 */
		list_add_rcu(&vif_priv->list, &ar->vif_list);
	} else {
		/* Add new inteface. If the list is empty, it will become the
		 * main inteface, otherwise it will be slave.
		 */
		list_add_tail_rcu(&vif_priv->list, &ar->vif_list);
	}
	rcu_assign_pointer(ar->vif_priv[vif_id].vif, vif);

init:
	main_vif = carl9170_get_main_vif(ar);

	if (main_vif == vif) {
		rcu_assign_pointer(ar->beacon_iter, vif_priv);
		rcu_read_unlock();

		if (old_main) {
			struct carl9170_vif_info *old_main_priv =
				(void *) old_main->drv_priv;
			/* downgrade old main intf to slave intf.
			 * NOTE: We are no longer under rcu_read_lock.
			 * But we are still holding ar->mutex, so the
			 * vif data [id, addr] is safe.
			 */
			err = carl9170_mod_virtual_mac(ar, old_main_priv->id,
						       old_main->addr);
			if (err)
				goto unlock;
		}

		err = carl9170_init_interface(ar, vif);
		if (err)
			goto unlock;
	} else {
		rcu_read_unlock();
		err = carl9170_mod_virtual_mac(ar, vif_id, vif->addr);

		if (err)
			goto unlock;
	}

	if (ar->fw.tx_seq_table) {
		err = carl9170_write_reg(ar, ar->fw.tx_seq_table + vif_id * 4,
					 0);
		if (err)
			goto unlock;
	}

unlock:
	if (err && (vif_id >= 0)) {
		vif_priv->active = false;
		bitmap_release_region(&ar->vif_bitmap, vif_id, 0);
		ar->vifs--;
		RCU_INIT_POINTER(ar->vif_priv[vif_id].vif, NULL);
		list_del_rcu(&vif_priv->list);
		mutex_unlock(&ar->mutex);
		synchronize_rcu();
	} else {
		if (ar->vifs > 1)
			ar->ps.off_override |= PS_OFF_VIF;

		mutex_unlock(&ar->mutex);
	}

	return err;
}