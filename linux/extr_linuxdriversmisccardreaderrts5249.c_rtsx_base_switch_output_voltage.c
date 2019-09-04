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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_PCI_PID (struct rtsx_pcr*,int) ; 
 int EINVAL ; 
#define  OUTPUT_1V8 129 
#define  OUTPUT_3V3 128 
 int /*<<< orphan*/  PHY_BACR ; 
 int /*<<< orphan*/  PHY_BACR_BASIC_MASK ; 
 int /*<<< orphan*/  PHY_TUNE ; 
 int /*<<< orphan*/  PHY_TUNE_D18_1V7 ; 
 int /*<<< orphan*/  PHY_TUNE_D18_1V8 ; 
 int /*<<< orphan*/  PHY_TUNE_VOLTAGE_3V3 ; 
 int /*<<< orphan*/  PHY_TUNE_VOLTAGE_MASK ; 
 int /*<<< orphan*/  pcr_dbg (struct rtsx_pcr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rts5249_fill_driving (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_init_cmd (struct rtsx_pcr*) ; 
 int rtsx_pci_send_cmd (struct rtsx_pcr*,int) ; 
 int rtsx_pci_update_phy (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtsx_base_switch_output_voltage(struct rtsx_pcr *pcr, u8 voltage)
{
	int err;
	u16 append;

	switch (voltage) {
	case OUTPUT_3V3:
		err = rtsx_pci_update_phy(pcr, PHY_TUNE, PHY_TUNE_VOLTAGE_MASK,
			PHY_TUNE_VOLTAGE_3V3);
		if (err < 0)
			return err;
		break;
	case OUTPUT_1V8:
		append = PHY_TUNE_D18_1V8;
		if (CHK_PCI_PID(pcr, 0x5249)) {
			err = rtsx_pci_update_phy(pcr, PHY_BACR,
				PHY_BACR_BASIC_MASK, 0);
			if (err < 0)
				return err;
			append = PHY_TUNE_D18_1V7;
		}

		err = rtsx_pci_update_phy(pcr, PHY_TUNE, PHY_TUNE_VOLTAGE_MASK,
			append);
		if (err < 0)
			return err;
		break;
	default:
		pcr_dbg(pcr, "unknown output voltage %d\n", voltage);
		return -EINVAL;
	}

	/* set pad drive */
	rtsx_pci_init_cmd(pcr);
	rts5249_fill_driving(pcr, voltage);
	return rtsx_pci_send_cmd(pcr, 100);
}