#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qlc_83xx_idc {int /*<<< orphan*/  status; } ;
struct qlcnic_hardware_context {scalar_t__ nic_mode; struct qlc_83xx_idc idc; } ;
struct qlcnic_adapter {int /*<<< orphan*/  idc_aen_work; int /*<<< orphan*/  fw_work; struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 scalar_t__ QLCNIC_VNIC_MODE ; 
 int /*<<< orphan*/  QLC_83XX_MBX_READY ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_83xx_disable_vnic_mode (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_detach_driver (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_initialize_nic (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 

void qlcnic_83xx_aer_stop_poll_work(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlc_83xx_idc *idc = &ahw->idc;

	clear_bit(QLC_83XX_MBX_READY, &idc->status);
	cancel_delayed_work_sync(&adapter->fw_work);

	if (ahw->nic_mode == QLCNIC_VNIC_MODE)
		qlcnic_83xx_disable_vnic_mode(adapter, 1);

	qlcnic_83xx_idc_detach_driver(adapter);
	qlcnic_83xx_initialize_nic(adapter, 0);

	cancel_delayed_work_sync(&adapter->idc_aen_work);
}