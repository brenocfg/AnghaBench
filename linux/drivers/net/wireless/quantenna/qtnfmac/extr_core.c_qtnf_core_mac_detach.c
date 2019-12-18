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
struct wiphy {TYPE_3__** bands; } ;
struct TYPE_4__ {TYPE_3__* wowlan; } ;
struct qtnf_wmac {TYPE_3__* rd; TYPE_1__ macinfo; scalar_t__ wiphy_registered; struct qtnf_vif* iflist; } ;
struct TYPE_5__ {scalar_t__ iftype; } ;
struct qtnf_vif {int /*<<< orphan*/  stats64; int /*<<< orphan*/  sta_list; TYPE_2__ wdev; scalar_t__ netdev; } ;
struct qtnf_bus {struct qtnf_wmac** mac; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_6__ {scalar_t__ n_channels; struct TYPE_6__* channels; } ;

/* Variables and functions */
 int NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_IFTYPE_UNSPECIFIED ; 
 int NUM_NL80211_BANDS ; 
 unsigned int QTNF_MAX_INTF ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 struct wiphy* priv_to_wiphy (struct qtnf_wmac*) ; 
 int /*<<< orphan*/  qtnf_del_virtual_intf (struct wiphy*,TYPE_2__*) ; 
 int /*<<< orphan*/  qtnf_mac_ext_caps_free (struct qtnf_wmac*) ; 
 int /*<<< orphan*/  qtnf_mac_iface_comb_free (struct qtnf_wmac*) ; 
 int /*<<< orphan*/  qtnf_sta_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qtnf_virtual_intf_cleanup (scalar_t__) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  wiphy_free (struct wiphy*) ; 
 int /*<<< orphan*/  wiphy_unregister (struct wiphy*) ; 

__attribute__((used)) static void qtnf_core_mac_detach(struct qtnf_bus *bus, unsigned int macid)
{
	struct qtnf_wmac *mac;
	struct wiphy *wiphy;
	struct qtnf_vif *vif;
	unsigned int i;
	enum nl80211_band band;

	mac = bus->mac[macid];

	if (!mac)
		return;

	wiphy = priv_to_wiphy(mac);

	for (i = 0; i < QTNF_MAX_INTF; i++) {
		vif = &mac->iflist[i];
		rtnl_lock();
		if (vif->netdev &&
		    vif->wdev.iftype != NL80211_IFTYPE_UNSPECIFIED) {
			qtnf_virtual_intf_cleanup(vif->netdev);
			qtnf_del_virtual_intf(wiphy, &vif->wdev);
		}
		rtnl_unlock();
		qtnf_sta_list_free(&vif->sta_list);
		free_percpu(vif->stats64);
	}

	if (mac->wiphy_registered)
		wiphy_unregister(wiphy);

	for (band = NL80211_BAND_2GHZ; band < NUM_NL80211_BANDS; ++band) {
		if (!wiphy->bands[band])
			continue;

		kfree(wiphy->bands[band]->channels);
		wiphy->bands[band]->n_channels = 0;

		kfree(wiphy->bands[band]);
		wiphy->bands[band] = NULL;
	}

	qtnf_mac_iface_comb_free(mac);
	qtnf_mac_ext_caps_free(mac);
	kfree(mac->macinfo.wowlan);
	kfree(mac->rd);
	mac->rd = NULL;
	wiphy_free(wiphy);
	bus->mac[macid] = NULL;
}