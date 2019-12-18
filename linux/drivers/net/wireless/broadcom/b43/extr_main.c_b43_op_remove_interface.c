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
struct ieee80211_vif {int /*<<< orphan*/  type; } ;
struct ieee80211_hw {int dummy; } ;
struct b43_wldev {int dummy; } ;
struct b43_wl {int operating; int /*<<< orphan*/  mutex; int /*<<< orphan*/  mac_addr; struct ieee80211_vif* vif; struct b43_wldev* current_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_adjust_opmode (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_upload_card_macaddress (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43dbg (struct b43_wl*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 struct b43_wl* hw_to_b43_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43_op_remove_interface(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif)
{
	struct b43_wl *wl = hw_to_b43_wl(hw);
	struct b43_wldev *dev = wl->current_dev;

	b43dbg(wl, "Removing Interface type %d\n", vif->type);

	mutex_lock(&wl->mutex);

	B43_WARN_ON(!wl->operating);
	B43_WARN_ON(wl->vif != vif);
	wl->vif = NULL;

	wl->operating = false;

	b43_adjust_opmode(dev);
	eth_zero_addr(wl->mac_addr);
	b43_upload_card_macaddress(dev);

	mutex_unlock(&wl->mutex);
}