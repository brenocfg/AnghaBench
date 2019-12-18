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
typedef  int uint16_t ;
struct TYPE_2__ {scalar_t__ rev; } ;
struct adapter {int /*<<< orphan*/  pdev; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PL_RST ; 
 int F_CRSTWRM ; 
 int F_CRSTWRMMODE ; 
 scalar_t__ T3_REV_B2 ; 
 scalar_t__ is_pcie (struct adapter*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_restore_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_save_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

int t3_reset_adapter(struct adapter *adapter)
{
	int i, save_and_restore_pcie =
	    adapter->params.rev < T3_REV_B2 && is_pcie(adapter);
	uint16_t devid = 0;

	if (save_and_restore_pcie)
		pci_save_state(adapter->pdev);
	t3_write_reg(adapter, A_PL_RST, F_CRSTWRM | F_CRSTWRMMODE);

	/*
	 * Delay. Give Some time to device to reset fully.
	 * XXX The delay time should be modified.
	 */
	for (i = 0; i < 10; i++) {
		msleep(50);
		pci_read_config_word(adapter->pdev, 0x00, &devid);
		if (devid == 0x1425)
			break;
	}

	if (devid != 0x1425)
		return -1;

	if (save_and_restore_pcie)
		pci_restore_state(adapter->pdev);
	return 0;
}