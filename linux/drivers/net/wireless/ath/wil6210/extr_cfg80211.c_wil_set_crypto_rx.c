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
struct wil_tid_crypto_rx_single {int key_set; int /*<<< orphan*/  pn; } ;
struct TYPE_4__ {struct wil_tid_crypto_rx_single* key_id; } ;
struct wil_sta_info {TYPE_2__ group_crypto_rx; TYPE_1__* tid_crypto_rx; } ;
struct key_params {int /*<<< orphan*/  seq; } ;
typedef  enum wmi_key_usage { ____Placeholder_wmi_key_usage } wmi_key_usage ;
struct TYPE_3__ {struct wil_tid_crypto_rx_single* key_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_GCMP_PN_LEN ; 
 int WIL_STA_TID_NUM ; 
#define  WMI_KEY_USE_PAIRWISE 130 
#define  WMI_KEY_USE_RX_GROUP 129 
#define  WMI_KEY_USE_STORE_PTK 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wil_set_crypto_rx(u8 key_index, enum wmi_key_usage key_usage,
		       struct wil_sta_info *cs,
		       struct key_params *params)
{
	struct wil_tid_crypto_rx_single *cc;
	int tid;

	if (!cs)
		return;

	switch (key_usage) {
	case WMI_KEY_USE_STORE_PTK:
	case WMI_KEY_USE_PAIRWISE:
		for (tid = 0; tid < WIL_STA_TID_NUM; tid++) {
			cc = &cs->tid_crypto_rx[tid].key_id[key_index];
			if (params->seq)
				memcpy(cc->pn, params->seq,
				       IEEE80211_GCMP_PN_LEN);
			else
				memset(cc->pn, 0, IEEE80211_GCMP_PN_LEN);
			cc->key_set = true;
		}
		break;
	case WMI_KEY_USE_RX_GROUP:
		cc = &cs->group_crypto_rx.key_id[key_index];
		if (params->seq)
			memcpy(cc->pn, params->seq, IEEE80211_GCMP_PN_LEN);
		else
			memset(cc->pn, 0, IEEE80211_GCMP_PN_LEN);
		cc->key_set = true;
		break;
	default:
		break;
	}
}