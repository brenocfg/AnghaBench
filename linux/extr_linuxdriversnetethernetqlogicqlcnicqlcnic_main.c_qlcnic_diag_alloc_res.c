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
struct qlcnic_host_sds_ring {int dummy; } ;
struct qlcnic_host_rds_ring {int dummy; } ;
struct qlcnic_adapter {int drv_sds_rings; int max_rds_rings; int /*<<< orphan*/  state; TYPE_2__* ahw; TYPE_1__* recv_ctx; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int diag_test; scalar_t__ loopback_state; scalar_t__ linkup; } ;
struct TYPE_3__ {struct qlcnic_host_sds_ring* sds_rings; struct qlcnic_host_rds_ring* rds_rings; } ;

/* Variables and functions */
 int QLCNIC_INTERRUPT_TEST ; 
 int QLCNIC_LOOPBACK_TEST ; 
 int QLCNIC_SINGLE_RING ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 int /*<<< orphan*/  __qlcnic_down (struct qlcnic_adapter*,struct net_device*) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int qlcnic_attach (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_detach (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_enable_sds_intr (struct qlcnic_adapter*,struct qlcnic_host_sds_ring*) ; 
 int qlcnic_fw_create_ctx (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_linkevent_request (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_post_rx_buffers (struct qlcnic_adapter*,struct qlcnic_host_rds_ring*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qlcnic_diag_alloc_res(struct net_device *netdev, int test)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_host_sds_ring *sds_ring;
	struct qlcnic_host_rds_ring *rds_ring;
	int ring;
	int ret;

	netif_device_detach(netdev);

	if (netif_running(netdev))
		__qlcnic_down(adapter, netdev);

	qlcnic_detach(adapter);

	adapter->drv_sds_rings = QLCNIC_SINGLE_RING;
	adapter->ahw->diag_test = test;
	adapter->ahw->linkup = 0;

	ret = qlcnic_attach(adapter);
	if (ret) {
		netif_device_attach(netdev);
		return ret;
	}

	ret = qlcnic_fw_create_ctx(adapter);
	if (ret) {
		qlcnic_detach(adapter);
		netif_device_attach(netdev);
		return ret;
	}

	for (ring = 0; ring < adapter->max_rds_rings; ring++) {
		rds_ring = &adapter->recv_ctx->rds_rings[ring];
		qlcnic_post_rx_buffers(adapter, rds_ring, ring);
	}

	if (adapter->ahw->diag_test == QLCNIC_INTERRUPT_TEST) {
		for (ring = 0; ring < adapter->drv_sds_rings; ring++) {
			sds_ring = &adapter->recv_ctx->sds_rings[ring];
			qlcnic_enable_sds_intr(adapter, sds_ring);
		}
	}

	if (adapter->ahw->diag_test == QLCNIC_LOOPBACK_TEST) {
		adapter->ahw->loopback_state = 0;
		qlcnic_linkevent_request(adapter, 1);
	}

	set_bit(__QLCNIC_DEV_UP, &adapter->state);

	return 0;
}