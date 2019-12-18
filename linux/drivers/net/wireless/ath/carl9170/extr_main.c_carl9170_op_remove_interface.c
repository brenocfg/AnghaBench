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
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ar9170* priv; } ;
struct carl9170_vif_info {int active; unsigned int id; int enable_beacon; int /*<<< orphan*/ * beacon; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  off_override; } ;
struct ar9170 {int vifs; int /*<<< orphan*/  mutex; TYPE_2__ ps; int /*<<< orphan*/  vif_bitmap; int /*<<< orphan*/  beacon_lock; TYPE_1__* vif_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS_OFF_VIF ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carl9170_flush_cab (struct ar9170*,unsigned int) ; 
 struct ieee80211_vif* carl9170_get_main_vif (struct ar9170*) ; 
 int carl9170_init_interface (struct ar9170*,struct ieee80211_vif*) ; 
 int carl9170_mod_virtual_mac (struct ar9170*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carl9170_set_beacon_timers (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_set_operating_mode (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_update_beacon (struct ar9170*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void carl9170_op_remove_interface(struct ieee80211_hw *hw,
					 struct ieee80211_vif *vif)
{
	struct carl9170_vif_info *vif_priv = (void *) vif->drv_priv;
	struct ieee80211_vif *main_vif;
	struct ar9170 *ar = hw->priv;
	unsigned int id;

	mutex_lock(&ar->mutex);

	if (WARN_ON_ONCE(!vif_priv->active))
		goto unlock;

	ar->vifs--;

	rcu_read_lock();
	main_vif = carl9170_get_main_vif(ar);

	id = vif_priv->id;

	vif_priv->active = false;
	WARN_ON(vif_priv->enable_beacon);
	vif_priv->enable_beacon = false;
	list_del_rcu(&vif_priv->list);
	RCU_INIT_POINTER(ar->vif_priv[id].vif, NULL);

	if (vif == main_vif) {
		rcu_read_unlock();

		if (ar->vifs) {
			WARN_ON(carl9170_init_interface(ar,
					carl9170_get_main_vif(ar)));
		} else {
			carl9170_set_operating_mode(ar);
		}
	} else {
		rcu_read_unlock();

		WARN_ON(carl9170_mod_virtual_mac(ar, id, NULL));
	}

	carl9170_update_beacon(ar, false);
	carl9170_flush_cab(ar, id);

	spin_lock_bh(&ar->beacon_lock);
	dev_kfree_skb_any(vif_priv->beacon);
	vif_priv->beacon = NULL;
	spin_unlock_bh(&ar->beacon_lock);

	bitmap_release_region(&ar->vif_bitmap, id, 0);

	carl9170_set_beacon_timers(ar);

	if (ar->vifs == 1)
		ar->ps.off_override &= ~PS_OFF_VIF;

unlock:
	mutex_unlock(&ar->mutex);

	synchronize_rcu();
}