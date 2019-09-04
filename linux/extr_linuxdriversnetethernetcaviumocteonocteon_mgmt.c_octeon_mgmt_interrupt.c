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
struct TYPE_2__ {scalar_t__ orthresh; scalar_t__ irthresh; } ;
union cvmx_mixx_isr {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
struct octeon_mgmt {int /*<<< orphan*/  tx_clean_tasklet; int /*<<< orphan*/  napi; scalar_t__ mix; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MIX_ISR ; 
 int /*<<< orphan*/  cvmx_read_csr (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct octeon_mgmt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  octeon_mgmt_disable_rx_irq (struct octeon_mgmt*) ; 
 int /*<<< orphan*/  octeon_mgmt_disable_tx_irq (struct octeon_mgmt*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t octeon_mgmt_interrupt(int cpl, void *dev_id)
{
	struct net_device *netdev = dev_id;
	struct octeon_mgmt *p = netdev_priv(netdev);
	union cvmx_mixx_isr mixx_isr;

	mixx_isr.u64 = cvmx_read_csr(p->mix + MIX_ISR);

	/* Clear any pending interrupts */
	cvmx_write_csr(p->mix + MIX_ISR, mixx_isr.u64);
	cvmx_read_csr(p->mix + MIX_ISR);

	if (mixx_isr.s.irthresh) {
		octeon_mgmt_disable_rx_irq(p);
		napi_schedule(&p->napi);
	}
	if (mixx_isr.s.orthresh) {
		octeon_mgmt_disable_tx_irq(p);
		tasklet_schedule(&p->tx_clean_tasklet);
	}

	return IRQ_HANDLED;
}