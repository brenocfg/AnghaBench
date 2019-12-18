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
struct hfi1_devdata {size_t hfi1_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_PCIE_SERDES ; 
 int /*<<< orphan*/  SPICO_SBUS ; 
 int /*<<< orphan*/  all_pcie_serdes_broadcast ; 
 int /*<<< orphan*/  clear_sbus_fast_mode (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  fw_pcie ; 
 scalar_t__ fw_pcie_serdes_load ; 
 int /*<<< orphan*/  fw_sbus ; 
 scalar_t__ fw_sbus_load ; 
 int load_pcie_serdes_firmware (struct hfi1_devdata*,int /*<<< orphan*/ *) ; 
 int load_sbus_firmware (struct hfi1_devdata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pcie_serdes_addrs ; 
 int /*<<< orphan*/ * pcie_serdes_broadcast ; 
 scalar_t__ retry_firmware (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  set_sbus_fast_mode (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  set_serdes_broadcast (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turn_off_spicos (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 

int load_pcie_firmware(struct hfi1_devdata *dd)
{
	int ret = 0;

	/* both firmware loads below use the SBus */
	set_sbus_fast_mode(dd);

	if (fw_sbus_load) {
		turn_off_spicos(dd, SPICO_SBUS);
		do {
			ret = load_sbus_firmware(dd, &fw_sbus);
		} while (retry_firmware(dd, ret));
		if (ret)
			goto done;
	}

	if (fw_pcie_serdes_load) {
		dd_dev_info(dd, "Setting PCIe SerDes broadcast\n");
		set_serdes_broadcast(dd, all_pcie_serdes_broadcast,
				     pcie_serdes_broadcast[dd->hfi1_id],
				     pcie_serdes_addrs[dd->hfi1_id],
				     NUM_PCIE_SERDES);
		do {
			ret = load_pcie_serdes_firmware(dd, &fw_pcie);
		} while (retry_firmware(dd, ret));
		if (ret)
			goto done;
	}

done:
	clear_sbus_fast_mode(dd);

	return ret;
}