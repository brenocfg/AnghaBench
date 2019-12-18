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
struct TYPE_6__ {int /*<<< orphan*/  eth_mtu; } ;
struct TYPE_4__ {int /*<<< orphan*/  eth_link_status; int /*<<< orphan*/  config_state; int /*<<< orphan*/  max_smac_ent; int /*<<< orphan*/  max_mac_tbl_ent; } ;
struct TYPE_5__ {TYPE_3__ vesw; TYPE_1__ vport; } ;
struct opa_vnic_adapter {TYPE_2__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_DATA_LEN ; 
 int /*<<< orphan*/  OPA_VNIC_ETH_LINK_DOWN ; 
 int /*<<< orphan*/  OPA_VNIC_MAC_TBL_MAX_ENTRIES ; 
 int /*<<< orphan*/  OPA_VNIC_MAX_SMAC_LIMIT ; 
 int /*<<< orphan*/  OPA_VNIC_STATE_DROP_ALL ; 

__attribute__((used)) static inline void opa_vnic_set_pod_values(struct opa_vnic_adapter *adapter)
{
	adapter->info.vport.max_mac_tbl_ent = OPA_VNIC_MAC_TBL_MAX_ENTRIES;
	adapter->info.vport.max_smac_ent = OPA_VNIC_MAX_SMAC_LIMIT;
	adapter->info.vport.config_state = OPA_VNIC_STATE_DROP_ALL;
	adapter->info.vport.eth_link_status = OPA_VNIC_ETH_LINK_DOWN;
	adapter->info.vesw.eth_mtu = ETH_DATA_LEN;
}