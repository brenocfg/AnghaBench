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
struct qlcnic_recv_context {struct qlcnic_host_tx_ring* sds_rings; } ;
struct qlcnic_host_tx_ring {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct qlcnic_host_sds_ring {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct qlcnic_adapter {int flags; int drv_sds_rings; int drv_tx_rings; struct qlcnic_host_tx_ring* tx_ring; TYPE_1__* ahw; int /*<<< orphan*/  irq; struct qlcnic_recv_context* recv_ctx; struct net_device* netdev; } ;
struct net_device {char* name; int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
struct TYPE_2__ {scalar_t__ diag_test; } ;

/* Variables and functions */
 unsigned long IRQF_SHARED ; 
 scalar_t__ QLCNIC_INTERRUPT_TEST ; 
 int /*<<< orphan*/  QLCNIC_IS_MSI_FAMILY (struct qlcnic_adapter*) ; 
 scalar_t__ QLCNIC_LOOPBACK_TEST ; 
 int QLCNIC_MSIX_ENABLED ; 
 int QLCNIC_MSI_ENABLED ; 
 int QLCNIC_TX_INTR_SHARED ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_intr ; 
 int /*<<< orphan*/  qlcnic_83xx_tmp_intr ; 
 scalar_t__ qlcnic_check_multi_tx (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_intr ; 
 int /*<<< orphan*/  qlcnic_msi_intr ; 
 int /*<<< orphan*/  qlcnic_msix_intr ; 
 int /*<<< orphan*/  qlcnic_msix_tx_intr ; 
 int /*<<< orphan*/  qlcnic_tmp_intr ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct qlcnic_host_tx_ring*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 

__attribute__((used)) static int
qlcnic_request_irq(struct qlcnic_adapter *adapter)
{
	irq_handler_t handler;
	struct qlcnic_host_sds_ring *sds_ring;
	struct qlcnic_host_tx_ring *tx_ring;
	int err, ring, num_sds_rings;

	unsigned long flags = 0;
	struct net_device *netdev = adapter->netdev;
	struct qlcnic_recv_context *recv_ctx = adapter->recv_ctx;

	if (adapter->ahw->diag_test == QLCNIC_INTERRUPT_TEST) {
		if (qlcnic_82xx_check(adapter))
			handler = qlcnic_tmp_intr;
		else
			handler = qlcnic_83xx_tmp_intr;
		if (!QLCNIC_IS_MSI_FAMILY(adapter))
			flags |= IRQF_SHARED;

	} else {
		if (adapter->flags & QLCNIC_MSIX_ENABLED)
			handler = qlcnic_msix_intr;
		else if (adapter->flags & QLCNIC_MSI_ENABLED)
			handler = qlcnic_msi_intr;
		else {
			flags |= IRQF_SHARED;
			if (qlcnic_82xx_check(adapter))
				handler = qlcnic_intr;
			else
				handler = qlcnic_83xx_intr;
		}
	}
	adapter->irq = netdev->irq;

	if (adapter->ahw->diag_test != QLCNIC_LOOPBACK_TEST) {
		if (qlcnic_82xx_check(adapter) ||
		    (qlcnic_83xx_check(adapter) &&
		     (adapter->flags & QLCNIC_MSIX_ENABLED))) {
			num_sds_rings = adapter->drv_sds_rings;
			for (ring = 0; ring < num_sds_rings; ring++) {
				sds_ring = &recv_ctx->sds_rings[ring];
				if (qlcnic_82xx_check(adapter) &&
				    !qlcnic_check_multi_tx(adapter) &&
				    (ring == (num_sds_rings - 1))) {
					if (!(adapter->flags &
					      QLCNIC_MSIX_ENABLED))
						snprintf(sds_ring->name,
							 sizeof(sds_ring->name),
							 "qlcnic");
					else
						snprintf(sds_ring->name,
							 sizeof(sds_ring->name),
							 "%s-tx-0-rx-%d",
							 netdev->name, ring);
				} else {
					snprintf(sds_ring->name,
						 sizeof(sds_ring->name),
						 "%s-rx-%d",
						 netdev->name, ring);
				}
				err = request_irq(sds_ring->irq, handler, flags,
						  sds_ring->name, sds_ring);
				if (err)
					return err;
			}
		}
		if ((qlcnic_82xx_check(adapter) &&
		     qlcnic_check_multi_tx(adapter)) ||
		    (qlcnic_83xx_check(adapter) &&
		     (adapter->flags & QLCNIC_MSIX_ENABLED) &&
		     !(adapter->flags & QLCNIC_TX_INTR_SHARED))) {
			handler = qlcnic_msix_tx_intr;
			for (ring = 0; ring < adapter->drv_tx_rings;
			     ring++) {
				tx_ring = &adapter->tx_ring[ring];
				snprintf(tx_ring->name, sizeof(tx_ring->name),
					 "%s-tx-%d", netdev->name, ring);
				err = request_irq(tx_ring->irq, handler, flags,
						  tx_ring->name, tx_ring);
				if (err)
					return err;
			}
		}
	}
	return 0;
}