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
struct iwl_rx_packet {int /*<<< orphan*/  data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ampdu_count; } ;
struct TYPE_4__ {int phy_flags; } ;
struct iwl_mvm {int /*<<< orphan*/  drv_stats_lock; TYPE_1__ drv_rx_stats; TYPE_2__ last_phy_info; int /*<<< orphan*/  ampdu_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_RES_PHY_FLAGS_AGG ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void iwl_mvm_rx_rx_phy_cmd(struct iwl_mvm *mvm, struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);

	memcpy(&mvm->last_phy_info, pkt->data, sizeof(mvm->last_phy_info));
	mvm->ampdu_ref++;

#ifdef CONFIG_IWLWIFI_DEBUGFS
	if (mvm->last_phy_info.phy_flags & cpu_to_le16(RX_RES_PHY_FLAGS_AGG)) {
		spin_lock(&mvm->drv_stats_lock);
		mvm->drv_rx_stats.ampdu_count++;
		spin_unlock(&mvm->drv_stats_lock);
	}
#endif
}