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
typedef  scalar_t__ u32 ;
struct qlc_83xx_idc {int /*<<< orphan*/  prev_state; } ;
struct qlcnic_hardware_context {scalar_t__ pci_func; struct qlc_83xx_idc idc; } ;
struct qlcnic_adapter {struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_83XX_IDC_DEV_READY ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_enter_ready_state (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_83xx_idc_find_reset_owner_id (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_poll_dev_state ; 
 int /*<<< orphan*/  qlcnic_schedule_work (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qlcnic_83xx_aer_start_poll_work(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlc_83xx_idc *idc = &ahw->idc;
	u32 owner;

	idc->prev_state = QLC_83XX_IDC_DEV_READY;
	owner = qlcnic_83xx_idc_find_reset_owner_id(adapter);
	if (ahw->pci_func == owner)
		qlcnic_83xx_idc_enter_ready_state(adapter, 0);

	qlcnic_schedule_work(adapter, qlcnic_83xx_idc_poll_dev_state, 0);
}