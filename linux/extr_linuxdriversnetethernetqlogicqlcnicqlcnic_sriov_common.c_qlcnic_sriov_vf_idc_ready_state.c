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
struct TYPE_2__ {scalar_t__ prev_state; } ;
struct qlcnic_hardware_context {scalar_t__ reset_context; TYPE_1__ idc; } ;
struct qlcnic_adapter {int /*<<< orphan*/  state; struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 scalar_t__ QLC_83XX_IDC_DEV_READY ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qlcnic_sriov_vf_handle_context_reset (struct qlcnic_adapter*) ; 
 int qlcnic_sriov_vf_handle_dev_ready (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_sriov_vf_idc_ready_state(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	int ret = 0;

	if (ahw->idc.prev_state != QLC_83XX_IDC_DEV_READY)
		ret = qlcnic_sriov_vf_handle_dev_ready(adapter);
	else if (ahw->reset_context)
		ret = qlcnic_sriov_vf_handle_context_reset(adapter);

	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	return ret;
}