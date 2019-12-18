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
 int /*<<< orphan*/  CR_SBUS ; 
 int /*<<< orphan*/  NUM_FABRIC_SERDES ; 
 int /*<<< orphan*/  SBUS_TIMEOUT ; 
 int /*<<< orphan*/  SPICO_FABRIC ; 
 int acquire_chip_resource (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_fabric_serdes_broadcast ; 
 int /*<<< orphan*/  clear_sbus_fast_mode (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  dump_fw_version (struct hfi1_devdata*) ; 
 int /*<<< orphan*/ * fabric_serdes_addrs ; 
 int /*<<< orphan*/ * fabric_serdes_broadcast ; 
 int /*<<< orphan*/  fw_8051 ; 
 scalar_t__ fw_8051_load ; 
 int /*<<< orphan*/  fw_fabric ; 
 scalar_t__ fw_fabric_serdes_load ; 
 int load_8051_firmware (struct hfi1_devdata*,int /*<<< orphan*/ *) ; 
 int load_fabric_serdes_firmware (struct hfi1_devdata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_chip_resource (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ retry_firmware (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  set_sbus_fast_mode (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  set_serdes_broadcast (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turn_off_spicos (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 

int load_firmware(struct hfi1_devdata *dd)
{
	int ret;

	if (fw_fabric_serdes_load) {
		ret = acquire_chip_resource(dd, CR_SBUS, SBUS_TIMEOUT);
		if (ret)
			return ret;

		set_sbus_fast_mode(dd);

		set_serdes_broadcast(dd, all_fabric_serdes_broadcast,
				     fabric_serdes_broadcast[dd->hfi1_id],
				     fabric_serdes_addrs[dd->hfi1_id],
				     NUM_FABRIC_SERDES);
		turn_off_spicos(dd, SPICO_FABRIC);
		do {
			ret = load_fabric_serdes_firmware(dd, &fw_fabric);
		} while (retry_firmware(dd, ret));

		clear_sbus_fast_mode(dd);
		release_chip_resource(dd, CR_SBUS);
		if (ret)
			return ret;
	}

	if (fw_8051_load) {
		do {
			ret = load_8051_firmware(dd, &fw_8051);
		} while (retry_firmware(dd, ret));
		if (ret)
			return ret;
	}

	dump_fw_version(dd);
	return 0;
}