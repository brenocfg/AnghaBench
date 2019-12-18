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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mt7615_vif {int /*<<< orphan*/  wmm_idx; } ;
struct TYPE_2__ {int beacon_int; int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  bssid; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; scalar_t__ drv_priv; } ;
struct bss_info_basic {int active; int /*<<< orphan*/  bmc_tx_wlan_idx; int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  wmm_idx; int /*<<< orphan*/  bssid; void* bcn_interval; int /*<<< orphan*/  network_type; void* len; void* tag; } ;

/* Variables and functions */
 int BSS_INFO_BASIC ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt7615_mcu_bss_info_basic_header(struct ieee80211_vif *vif, u8 *data,
				 u32 net_type, u8 tx_wlan_idx,
				 bool enable)
{
	struct mt7615_vif *mvif = (struct mt7615_vif *)vif->drv_priv;
	struct bss_info_basic *hdr = (struct bss_info_basic *)data;

	hdr->tag = cpu_to_le16(BSS_INFO_BASIC);
	hdr->len = cpu_to_le16(sizeof(struct bss_info_basic));
	hdr->network_type = cpu_to_le32(net_type);
	hdr->active = enable;
	hdr->bcn_interval = cpu_to_le16(vif->bss_conf.beacon_int);
	memcpy(hdr->bssid, vif->bss_conf.bssid, ETH_ALEN);
	hdr->wmm_idx = mvif->wmm_idx;
	hdr->dtim_period = vif->bss_conf.dtim_period;
	hdr->bmc_tx_wlan_idx = tx_wlan_idx;
}