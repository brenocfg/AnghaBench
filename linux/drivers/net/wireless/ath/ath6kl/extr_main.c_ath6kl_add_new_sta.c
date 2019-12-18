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
typedef  size_t u8 ;
typedef  void* u16 ;
struct ath6kl_vif {int /*<<< orphan*/  aggr_cntxt; struct ath6kl* ar; } ;
struct ath6kl_sta {size_t keymgmt; size_t ucipher; size_t auth; size_t apsd_info; int /*<<< orphan*/  aggr_conn; void* aid; int /*<<< orphan*/  wpa_ie; int /*<<< orphan*/  mac; } ;
struct TYPE_4__ {TYPE_1__* sta; } ;
struct ath6kl {int sta_list_index; TYPE_2__ ap_stats; struct ath6kl_sta* sta_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  aid; } ;

/* Variables and functions */
 size_t ATH6KL_MAX_IE ; 
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  aggr_conn_init (struct ath6kl_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,size_t*,size_t) ; 

__attribute__((used)) static void ath6kl_add_new_sta(struct ath6kl_vif *vif, u8 *mac, u16 aid,
			       u8 *wpaie, size_t ielen, u8 keymgmt,
			       u8 ucipher, u8 auth, u8 apsd_info)
{
	struct ath6kl *ar = vif->ar;
	struct ath6kl_sta *sta;
	u8 free_slot;

	free_slot = aid - 1;

	sta = &ar->sta_list[free_slot];
	memcpy(sta->mac, mac, ETH_ALEN);
	if (ielen <= ATH6KL_MAX_IE)
		memcpy(sta->wpa_ie, wpaie, ielen);
	sta->aid = aid;
	sta->keymgmt = keymgmt;
	sta->ucipher = ucipher;
	sta->auth = auth;
	sta->apsd_info = apsd_info;

	ar->sta_list_index = ar->sta_list_index | (1 << free_slot);
	ar->ap_stats.sta[free_slot].aid = cpu_to_le32(aid);
	aggr_conn_init(vif, vif->aggr_cntxt, sta->aggr_conn);
}