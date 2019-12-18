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
typedef  int u32 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_bss_conf {scalar_t__ use_short_slot; int /*<<< orphan*/  basic_rates; int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  bssid; } ;
struct b43legacy_wldev {int /*<<< orphan*/  irq_mask; } ;
struct b43legacy_wl {int /*<<< orphan*/  mutex; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  bssid; struct b43legacy_wldev* current_dev; struct ieee80211_vif* vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_MMIO_GEN_IRQ_MASK ; 
 scalar_t__ B43legacy_STAT_INITIALIZED ; 
 scalar_t__ B43legacy_STAT_STARTED ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int BSS_CHANGED_BASIC_RATES ; 
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_BSSID ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 scalar_t__ b43legacy_is_mode (struct b43legacy_wl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_mac_enable (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_mac_suspend (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_set_beacon_int (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_short_slot_timing_disable (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_short_slot_timing_enable (struct b43legacy_wldev*) ; 
 scalar_t__ b43legacy_status (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_synchronize_irq (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_update_basic_rates (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_update_templates (struct b43legacy_wl*) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write_mac_bssid_templates (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 struct b43legacy_wl* hw_to_b43legacy_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void b43legacy_op_bss_info_changed(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif,
				    struct ieee80211_bss_conf *conf,
				    u32 changed)
{
	struct b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	struct b43legacy_wldev *dev;
	unsigned long flags;

	mutex_lock(&wl->mutex);
	B43legacy_WARN_ON(wl->vif != vif);

	dev = wl->current_dev;

	/* Disable IRQs while reconfiguring the device.
	 * This makes it possible to drop the spinlock throughout
	 * the reconfiguration process. */
	spin_lock_irqsave(&wl->irq_lock, flags);
	if (b43legacy_status(dev) < B43legacy_STAT_STARTED) {
		spin_unlock_irqrestore(&wl->irq_lock, flags);
		goto out_unlock_mutex;
	}
	b43legacy_write32(dev, B43legacy_MMIO_GEN_IRQ_MASK, 0);

	if (changed & BSS_CHANGED_BSSID) {
		b43legacy_synchronize_irq(dev);

		if (conf->bssid)
			memcpy(wl->bssid, conf->bssid, ETH_ALEN);
		else
			eth_zero_addr(wl->bssid);
	}

	if (b43legacy_status(dev) >= B43legacy_STAT_INITIALIZED) {
		if (changed & BSS_CHANGED_BEACON &&
		    (b43legacy_is_mode(wl, NL80211_IFTYPE_AP) ||
		     b43legacy_is_mode(wl, NL80211_IFTYPE_ADHOC)))
			b43legacy_update_templates(wl);

		if (changed & BSS_CHANGED_BSSID)
			b43legacy_write_mac_bssid_templates(dev);
	}
	spin_unlock_irqrestore(&wl->irq_lock, flags);

	b43legacy_mac_suspend(dev);

	if (changed & BSS_CHANGED_BEACON_INT &&
	    (b43legacy_is_mode(wl, NL80211_IFTYPE_AP) ||
	     b43legacy_is_mode(wl, NL80211_IFTYPE_ADHOC)))
		b43legacy_set_beacon_int(dev, conf->beacon_int);

	if (changed & BSS_CHANGED_BASIC_RATES)
		b43legacy_update_basic_rates(dev, conf->basic_rates);

	if (changed & BSS_CHANGED_ERP_SLOT) {
		if (conf->use_short_slot)
			b43legacy_short_slot_timing_enable(dev);
		else
			b43legacy_short_slot_timing_disable(dev);
	}

	b43legacy_mac_enable(dev);

	spin_lock_irqsave(&wl->irq_lock, flags);
	b43legacy_write32(dev, B43legacy_MMIO_GEN_IRQ_MASK, dev->irq_mask);
	/* XXX: why? */
	spin_unlock_irqrestore(&wl->irq_lock, flags);
 out_unlock_mutex:
	mutex_unlock(&wl->mutex);
}