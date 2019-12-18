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
typedef  scalar_t__ u8 ;
struct rtsx_pcr {int /*<<< orphan*/  sd30_drive_sel_1v8; int /*<<< orphan*/  sd30_drive_sel_3v3; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OUTPUT_1V8 ; 
 scalar_t__ OUTPUT_3V3 ; 
 int /*<<< orphan*/  SD30_DRIVE_SEL ; 
 int rtsx_pci_write_phy_register (struct rtsx_pcr*,int,int) ; 
 int rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rts5229_switch_output_voltage(struct rtsx_pcr *pcr, u8 voltage)
{
	int err;

	if (voltage == OUTPUT_3V3) {
		err = rtsx_pci_write_register(pcr,
				SD30_DRIVE_SEL, 0x07, pcr->sd30_drive_sel_3v3);
		if (err < 0)
			return err;
		err = rtsx_pci_write_phy_register(pcr, 0x08, 0x4FC0 | 0x24);
		if (err < 0)
			return err;
	} else if (voltage == OUTPUT_1V8) {
		err = rtsx_pci_write_register(pcr,
				SD30_DRIVE_SEL, 0x07, pcr->sd30_drive_sel_1v8);
		if (err < 0)
			return err;
		err = rtsx_pci_write_phy_register(pcr, 0x08, 0x4C40 | 0x24);
		if (err < 0)
			return err;
	} else {
		return -EINVAL;
	}

	return 0;
}