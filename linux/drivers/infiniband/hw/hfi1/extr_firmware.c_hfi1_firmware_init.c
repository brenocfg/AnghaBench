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
struct hfi1_devdata {scalar_t__ icode; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_FW_8051_NAME_ASIC ; 
 scalar_t__ DEFAULT_FW_8051_NAME_FPGA ; 
 scalar_t__ DEFAULT_FW_FABRIC_NAME ; 
 scalar_t__ DEFAULT_FW_PCIE_NAME ; 
 scalar_t__ DEFAULT_FW_SBUS_NAME ; 
 scalar_t__ ICODE_FUNCTIONAL_SIMULATOR ; 
 scalar_t__ ICODE_RTL_SILICON ; 
 scalar_t__ fw_8051_load ; 
 scalar_t__ fw_8051_name ; 
 scalar_t__ fw_fabric_serdes_load ; 
 scalar_t__ fw_fabric_serdes_name ; 
 scalar_t__ fw_pcie_serdes_load ; 
 scalar_t__ fw_pcie_serdes_name ; 
 scalar_t__ fw_sbus_load ; 
 scalar_t__ fw_sbus_name ; 
 int obtain_firmware (struct hfi1_devdata*) ; 

int hfi1_firmware_init(struct hfi1_devdata *dd)
{
	/* only RTL can use these */
	if (dd->icode != ICODE_RTL_SILICON) {
		fw_fabric_serdes_load = 0;
		fw_pcie_serdes_load = 0;
		fw_sbus_load = 0;
	}

	/* no 8051 or QSFP on simulator */
	if (dd->icode == ICODE_FUNCTIONAL_SIMULATOR)
		fw_8051_load = 0;

	if (!fw_8051_name) {
		if (dd->icode == ICODE_RTL_SILICON)
			fw_8051_name = DEFAULT_FW_8051_NAME_ASIC;
		else
			fw_8051_name = DEFAULT_FW_8051_NAME_FPGA;
	}
	if (!fw_fabric_serdes_name)
		fw_fabric_serdes_name = DEFAULT_FW_FABRIC_NAME;
	if (!fw_sbus_name)
		fw_sbus_name = DEFAULT_FW_SBUS_NAME;
	if (!fw_pcie_serdes_name)
		fw_pcie_serdes_name = DEFAULT_FW_PCIE_NAME;

	return obtain_firmware(dd);
}