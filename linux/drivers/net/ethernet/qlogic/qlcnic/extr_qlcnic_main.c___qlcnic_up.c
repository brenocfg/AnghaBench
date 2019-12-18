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
struct qlcnic_host_rds_ring {int dummy; } ;
struct qlcnic_adapter {scalar_t__ is_up; int max_rds_rings; int drv_sds_rings; TYPE_2__* ahw; int /*<<< orphan*/  state; TYPE_1__* recv_ctx; } ;
struct net_device {int features; int /*<<< orphan*/  mtu; } ;
struct TYPE_4__ {scalar_t__ reset_context; scalar_t__ linkup; } ;
struct TYPE_3__ {struct qlcnic_host_rds_ring* rds_rings; } ;

/* Variables and functions */
 int EIO ; 
 int NETIF_F_LRO ; 
 scalar_t__ QLCNIC_ADAPTER_UP_MAGIC ; 
 int /*<<< orphan*/  QLCNIC_LRO_ENABLED ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_config_def_intr_coalesce (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_config_hw_lro (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_config_rss (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_fw_cmd_set_mtu (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_fw_create_ctx (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_get_lro_mss_capability (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_linkevent_request (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_napi_enable (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_post_rx_buffers (struct qlcnic_adapter*,struct qlcnic_host_rds_ring*,int) ; 
 scalar_t__ qlcnic_set_eswitch_port_config (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_set_multi (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int __qlcnic_up(struct qlcnic_adapter *adapter, struct net_device *netdev)
{
	int ring;
	struct qlcnic_host_rds_ring *rds_ring;

	if (adapter->is_up != QLCNIC_ADAPTER_UP_MAGIC)
		return -EIO;

	if (test_bit(__QLCNIC_DEV_UP, &adapter->state))
		return 0;

	if (qlcnic_set_eswitch_port_config(adapter))
		return -EIO;

	qlcnic_get_lro_mss_capability(adapter);

	if (qlcnic_fw_create_ctx(adapter))
		return -EIO;

	for (ring = 0; ring < adapter->max_rds_rings; ring++) {
		rds_ring = &adapter->recv_ctx->rds_rings[ring];
		qlcnic_post_rx_buffers(adapter, rds_ring, ring);
	}

	qlcnic_set_multi(netdev);
	qlcnic_fw_cmd_set_mtu(adapter, netdev->mtu);

	adapter->ahw->linkup = 0;

	if (adapter->drv_sds_rings > 1)
		qlcnic_config_rss(adapter, 1);

	qlcnic_config_def_intr_coalesce(adapter);

	if (netdev->features & NETIF_F_LRO)
		qlcnic_config_hw_lro(adapter, QLCNIC_LRO_ENABLED);

	set_bit(__QLCNIC_DEV_UP, &adapter->state);
	qlcnic_napi_enable(adapter);

	qlcnic_linkevent_request(adapter, 1);

	adapter->ahw->reset_context = 0;
	netif_tx_start_all_queues(netdev);
	return 0;
}