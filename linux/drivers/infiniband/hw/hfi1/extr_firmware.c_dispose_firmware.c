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

/* Variables and functions */
 scalar_t__ FW_EMPTY ; 
 scalar_t__ FW_ERR ; 
 int /*<<< orphan*/  dispose_one_firmware (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_8051 ; 
 int /*<<< orphan*/  fw_fabric ; 
 int /*<<< orphan*/  fw_pcie ; 
 int /*<<< orphan*/  fw_sbus ; 
 scalar_t__ fw_state ; 

void dispose_firmware(void)
{
	dispose_one_firmware(&fw_8051);
	dispose_one_firmware(&fw_fabric);
	dispose_one_firmware(&fw_pcie);
	dispose_one_firmware(&fw_sbus);

	/* retain the error state, otherwise revert to empty */
	if (fw_state != FW_ERR)
		fw_state = FW_EMPTY;
}