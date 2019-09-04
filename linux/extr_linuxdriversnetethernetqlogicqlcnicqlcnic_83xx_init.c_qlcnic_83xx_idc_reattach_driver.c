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
struct qlcnic_adapter {scalar_t__ portnum; int /*<<< orphan*/  dcb; TYPE_2__* nic_ops; TYPE_1__* ahw; } ;
struct TYPE_4__ {scalar_t__ (* init_driver ) (struct qlcnic_adapter*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  mailbox; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ qlcnic_83xx_configure_opmode (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_enable_mbx_interrupt (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_attach_driver (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_enter_failed_state (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_initialize_nic (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_reinit_mbx_work (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_dcb_get_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_set_drv_version (struct qlcnic_adapter*) ; 
 int qlcnic_sriov_pf_reinit (struct qlcnic_adapter*) ; 
 scalar_t__ stub1 (struct qlcnic_adapter*) ; 

int qlcnic_83xx_idc_reattach_driver(struct qlcnic_adapter *adapter)
{
	int err;

	qlcnic_83xx_reinit_mbx_work(adapter->ahw->mailbox);
	qlcnic_83xx_enable_mbx_interrupt(adapter);

	qlcnic_83xx_initialize_nic(adapter, 1);

	err = qlcnic_sriov_pf_reinit(adapter);
	if (err)
		return err;

	qlcnic_83xx_enable_mbx_interrupt(adapter);

	if (qlcnic_83xx_configure_opmode(adapter)) {
		qlcnic_83xx_idc_enter_failed_state(adapter, 1);
		return -EIO;
	}

	if (adapter->nic_ops->init_driver(adapter)) {
		qlcnic_83xx_idc_enter_failed_state(adapter, 1);
		return -EIO;
	}

	if (adapter->portnum == 0)
		qlcnic_set_drv_version(adapter);

	qlcnic_dcb_get_info(adapter->dcb);
	qlcnic_83xx_idc_attach_driver(adapter);

	return 0;
}