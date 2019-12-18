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
struct qlcnic_host_sds_ring {int /*<<< orphan*/  napi; } ;
struct qlcnic_hardware_context {scalar_t__ diag_test; int /*<<< orphan*/  diag_cnt; } ;
struct qlcnic_adapter {TYPE_1__* recv_ctx; int /*<<< orphan*/  state; struct qlcnic_hardware_context* ahw; } ;
typedef  scalar_t__ irqreturn_t ;
struct TYPE_2__ {struct qlcnic_host_sds_ring* sds_rings; } ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 scalar_t__ QLCNIC_INTERRUPT_TEST ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ qlcnic_83xx_clear_legacy_intr (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_enable_legacy_msix_mbx_intr (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_poll_process_aen (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

irqreturn_t qlcnic_83xx_intr(int irq, void *data)
{
	struct qlcnic_adapter *adapter = data;
	struct qlcnic_host_sds_ring *sds_ring;
	struct qlcnic_hardware_context *ahw = adapter->ahw;

	if (qlcnic_83xx_clear_legacy_intr(adapter) == IRQ_NONE)
		return IRQ_NONE;

	qlcnic_83xx_poll_process_aen(adapter);

	if (ahw->diag_test) {
		if (ahw->diag_test == QLCNIC_INTERRUPT_TEST)
			ahw->diag_cnt++;
		qlcnic_83xx_enable_legacy_msix_mbx_intr(adapter);
		return IRQ_HANDLED;
	}

	if (!test_bit(__QLCNIC_DEV_UP, &adapter->state)) {
		qlcnic_83xx_enable_legacy_msix_mbx_intr(adapter);
	} else {
		sds_ring = &adapter->recv_ctx->sds_rings[0];
		napi_schedule(&sds_ring->napi);
	}

	return IRQ_HANDLED;
}