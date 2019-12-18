#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int rx_max_rate; int rx_mcs_set; int tx_max_rate; int tx_mcs_set; } ;
struct TYPE_12__ {int num_rates; int /*<<< orphan*/  rates; } ;
struct TYPE_10__ {int num_rates; int /*<<< orphan*/  rates; } ;
struct wmi_peer_assoc_complete_arg {int vdev_id; int peer_aid; int peer_flags; int peer_caps; int peer_listen_intval; int peer_ht_caps; int peer_max_mpdu; int peer_mpdu_density; int peer_rate_caps; int peer_num_spatial_streams; int peer_vht_caps; int peer_phymode; TYPE_7__ peer_vht_rates; TYPE_5__ peer_ht_rates; TYPE_3__ peer_legacy_rates; int /*<<< orphan*/  addr; scalar_t__ peer_reassoc; } ;
struct TYPE_13__ {void* tx_mcs_set; void* tx_max_rate; void* rx_mcs_set; void* rx_max_rate; } ;
struct TYPE_11__ {int /*<<< orphan*/  rates; void* num_rates; } ;
struct TYPE_9__ {int /*<<< orphan*/  rates; void* num_rates; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct wmi_common_peer_assoc_complete_cmd {TYPE_6__ peer_vht_rates; TYPE_4__ peer_ht_rates; TYPE_2__ peer_legacy_rates; TYPE_1__ peer_macaddr; void* peer_phymode; void* peer_vht_caps; void* peer_nss; void* peer_rate_caps; void* peer_mpdu_density; void* peer_max_mpdu; void* peer_ht_caps; void* peer_listen_intval; void* peer_caps; void* peer_flags; void* peer_associd; void* peer_new_assoc; void* vdev_id; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ath10k_wmi_peer_assoc_fill(struct ath10k *ar, void *buf,
			   const struct wmi_peer_assoc_complete_arg *arg)
{
	struct wmi_common_peer_assoc_complete_cmd *cmd = buf;

	cmd->vdev_id            = __cpu_to_le32(arg->vdev_id);
	cmd->peer_new_assoc     = __cpu_to_le32(arg->peer_reassoc ? 0 : 1);
	cmd->peer_associd       = __cpu_to_le32(arg->peer_aid);
	cmd->peer_flags         = __cpu_to_le32(arg->peer_flags);
	cmd->peer_caps          = __cpu_to_le32(arg->peer_caps);
	cmd->peer_listen_intval = __cpu_to_le32(arg->peer_listen_intval);
	cmd->peer_ht_caps       = __cpu_to_le32(arg->peer_ht_caps);
	cmd->peer_max_mpdu      = __cpu_to_le32(arg->peer_max_mpdu);
	cmd->peer_mpdu_density  = __cpu_to_le32(arg->peer_mpdu_density);
	cmd->peer_rate_caps     = __cpu_to_le32(arg->peer_rate_caps);
	cmd->peer_nss           = __cpu_to_le32(arg->peer_num_spatial_streams);
	cmd->peer_vht_caps      = __cpu_to_le32(arg->peer_vht_caps);
	cmd->peer_phymode       = __cpu_to_le32(arg->peer_phymode);

	ether_addr_copy(cmd->peer_macaddr.addr, arg->addr);

	cmd->peer_legacy_rates.num_rates =
		__cpu_to_le32(arg->peer_legacy_rates.num_rates);
	memcpy(cmd->peer_legacy_rates.rates, arg->peer_legacy_rates.rates,
	       arg->peer_legacy_rates.num_rates);

	cmd->peer_ht_rates.num_rates =
		__cpu_to_le32(arg->peer_ht_rates.num_rates);
	memcpy(cmd->peer_ht_rates.rates, arg->peer_ht_rates.rates,
	       arg->peer_ht_rates.num_rates);

	cmd->peer_vht_rates.rx_max_rate =
		__cpu_to_le32(arg->peer_vht_rates.rx_max_rate);
	cmd->peer_vht_rates.rx_mcs_set =
		__cpu_to_le32(arg->peer_vht_rates.rx_mcs_set);
	cmd->peer_vht_rates.tx_max_rate =
		__cpu_to_le32(arg->peer_vht_rates.tx_max_rate);
	cmd->peer_vht_rates.tx_mcs_set =
		__cpu_to_le32(arg->peer_vht_rates.tx_mcs_set);
}