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
struct qtnf_wmac {struct qtnf_vif* iflist; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; int /*<<< orphan*/  iftype; } ;
struct qtnf_vif {scalar_t__ cons_tx_timeout_cnt; int /*<<< orphan*/  reset_work; TYPE_1__ wdev; int /*<<< orphan*/  bss_priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  QTNF_DEF_BSS_PRIORITY ; 
 size_t QTNF_PRIMARY_VIF_IDX ; 
 int /*<<< orphan*/  priv_to_wiphy (struct qtnf_wmac*) ; 
 int /*<<< orphan*/  qtnf_vif_reset_handler ; 

__attribute__((used)) static void qtnf_mac_init_primary_intf(struct qtnf_wmac *mac)
{
	struct qtnf_vif *vif = &mac->iflist[QTNF_PRIMARY_VIF_IDX];

	vif->wdev.iftype = NL80211_IFTYPE_STATION;
	vif->bss_priority = QTNF_DEF_BSS_PRIORITY;
	vif->wdev.wiphy = priv_to_wiphy(mac);
	INIT_WORK(&vif->reset_work, qtnf_vif_reset_handler);
	vif->cons_tx_timeout_cnt = 0;
}