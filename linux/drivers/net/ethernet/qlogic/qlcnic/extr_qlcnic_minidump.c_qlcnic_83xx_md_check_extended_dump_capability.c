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
struct qlcnic_adapter {TYPE_2__* ahw; TYPE_1__* pdev; } ;
struct TYPE_4__ {int* extra_capability; } ;
struct TYPE_3__ {scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_QLOGIC_QLE8830 ; 
 int QLCNIC_FW_CAPABILITY_2_EXT_ISCSI_DUMP ; 

__attribute__((used)) static inline bool
qlcnic_83xx_md_check_extended_dump_capability(struct qlcnic_adapter *adapter)
{
	/* For special adapters (with 0x8830 device ID), where iSCSI firmware
	 * dump needs to be captured as part of regular firmware dump
	 * collection process, firmware exports it's capability through
	 * capability registers
	 */
	return ((adapter->pdev->device == PCI_DEVICE_ID_QLOGIC_QLE8830) &&
		(adapter->ahw->extra_capability[0] &
		 QLCNIC_FW_CAPABILITY_2_EXT_ISCSI_DUMP));
}