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
struct qlcnic_adapter {int drv_tx_rings; int drv_sds_rings; TYPE_2__* ahw; TYPE_1__* recv_ctx; int /*<<< orphan*/  state; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ diag_test; } ;
struct TYPE_3__ {struct qlcnic_host_sds_ring* sds_rings; } ;

/* Variables and functions */
 scalar_t__ QLCNIC_INTERRUPT_TEST ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 int /*<<< orphan*/  __qlcnic_up (struct qlcnic_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ qlcnic_attach (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_detach (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_disable_sds_intr (struct qlcnic_adapter*,struct qlcnic_host_sds_ring*) ; 
 int /*<<< orphan*/  qlcnic_fw_destroy_ctx (struct qlcnic_adapter*) ; 

void qlcnic_diag_free_res(struct net_device *netdev, int drv_sds_rings)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_host_sds_ring *sds_ring;
	int drv_tx_rings = adapter->drv_tx_rings;
	int ring;

	clear_bit(__QLCNIC_DEV_UP, &adapter->state);
	if (adapter->ahw->diag_test == QLCNIC_INTERRUPT_TEST) {
		for (ring = 0; ring < adapter->drv_sds_rings; ring++) {
			sds_ring = &adapter->recv_ctx->sds_rings[ring];
			qlcnic_disable_sds_intr(adapter, sds_ring);
		}
	}

	qlcnic_fw_destroy_ctx(adapter);

	qlcnic_detach(adapter);

	adapter->ahw->diag_test = 0;
	adapter->drv_sds_rings = drv_sds_rings;
	adapter->drv_tx_rings = drv_tx_rings;

	if (qlcnic_attach(adapter))
		goto out;

	if (netif_running(netdev))
		__qlcnic_up(adapter, netdev);
out:
	netif_device_attach(netdev);
}