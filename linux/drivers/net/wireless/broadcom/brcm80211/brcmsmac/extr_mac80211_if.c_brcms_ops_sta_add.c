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
struct TYPE_5__ {int max_pdu; struct scb* scb; } ;
struct scb {TYPE_2__ scb_ampdu; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {struct brcms_info* priv; } ;
struct brcms_info {TYPE_3__* pub; TYPE_1__* wlc; } ;
struct TYPE_6__ {TYPE_2__* global_ampdu; } ;
struct TYPE_4__ {struct scb pri_scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_init_scb (struct scb*) ; 

__attribute__((used)) static int
brcms_ops_sta_add(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
	       struct ieee80211_sta *sta)
{
	struct brcms_info *wl = hw->priv;
	struct scb *scb = &wl->wlc->pri_scb;

	brcms_c_init_scb(scb);

	wl->pub->global_ampdu = &(scb->scb_ampdu);
	wl->pub->global_ampdu->scb = scb;
	wl->pub->global_ampdu->max_pdu = 16;

	/*
	 * minstrel_ht initiates addBA on our behalf by calling
	 * ieee80211_start_tx_ba_session()
	 */
	return 0;
}