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
typedef  size_t u8 ;
typedef  int u32 ;
struct wmi_per_sta_stat {int /*<<< orphan*/  rx_discard; int /*<<< orphan*/  rx_error; int /*<<< orphan*/  rx_pkts; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_discard; int /*<<< orphan*/  tx_error; int /*<<< orphan*/  tx_pkts; int /*<<< orphan*/  tx_bytes; } ;
struct wmi_ap_mode_stat {struct wmi_per_sta_stat* sta; } ;
struct ath6kl_vif {scalar_t__ nw_type; struct ath6kl* ar; } ;
struct ath6kl {struct wmi_ap_mode_stat ap_stats; } ;

/* Variables and functions */
 size_t AP_MAX_NUM_STA ; 
 scalar_t__ AP_NETWORK ; 
 int /*<<< orphan*/  ath6kl_add_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_update_target_stats (struct ath6kl_vif*,size_t*,int) ; 

void ath6kl_tgt_stats_event(struct ath6kl_vif *vif, u8 *ptr, u32 len)
{
	struct wmi_ap_mode_stat *p = (struct wmi_ap_mode_stat *) ptr;
	struct ath6kl *ar = vif->ar;
	struct wmi_ap_mode_stat *ap = &ar->ap_stats;
	struct wmi_per_sta_stat *st_ap, *st_p;
	u8 ac;

	if (vif->nw_type == AP_NETWORK) {
		if (len < sizeof(*p))
			return;

		for (ac = 0; ac < AP_MAX_NUM_STA; ac++) {
			st_ap = &ap->sta[ac];
			st_p = &p->sta[ac];

			ath6kl_add_le32(&st_ap->tx_bytes, st_p->tx_bytes);
			ath6kl_add_le32(&st_ap->tx_pkts, st_p->tx_pkts);
			ath6kl_add_le32(&st_ap->tx_error, st_p->tx_error);
			ath6kl_add_le32(&st_ap->tx_discard, st_p->tx_discard);
			ath6kl_add_le32(&st_ap->rx_bytes, st_p->rx_bytes);
			ath6kl_add_le32(&st_ap->rx_pkts, st_p->rx_pkts);
			ath6kl_add_le32(&st_ap->rx_error, st_p->rx_error);
			ath6kl_add_le32(&st_ap->rx_discard, st_p->rx_discard);
		}

	} else {
		ath6kl_update_target_stats(vif, ptr, len);
	}
}