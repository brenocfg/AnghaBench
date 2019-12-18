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
struct qlcnic_adapter {int /*<<< orphan*/  state; TYPE_2__* pdev; TYPE_1__* ahw; } ;
struct qlc_83xx_idc {scalar_t__ prev_state; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct qlc_83xx_idc idc; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ QLC_83XX_IDC_DEV_READY ; 
 int /*<<< orphan*/  QLC_83XX_MODULE_LOADED ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qlcnic_sriov_vf_detach (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_sriov_vf_idc_failed_state(struct qlcnic_adapter *adapter)
{
	struct qlc_83xx_idc *idc = &adapter->ahw->idc;

	dev_err(&adapter->pdev->dev, "Device is in failed state\n");
	if (idc->prev_state == QLC_83XX_IDC_DEV_READY)
		qlcnic_sriov_vf_detach(adapter);

	clear_bit(QLC_83XX_MODULE_LOADED, &idc->status);
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	return -EIO;
}