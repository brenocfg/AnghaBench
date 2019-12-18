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
typedef  int u8 ;
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DV331812_17 ; 
 int /*<<< orphan*/  DV331812_33 ; 
 int /*<<< orphan*/  DV331812_MASK ; 
 int /*<<< orphan*/  DV331812_VDD1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  LDO_CONFIG2 ; 
 int /*<<< orphan*/  LDO_DV18_CFG ; 
#define  OUTPUT_1V8 129 
#define  OUTPUT_3V3 128 
 int /*<<< orphan*/  SD_IO_USING_1V8 ; 
 int /*<<< orphan*/  SD_PAD_CTL ; 
 int /*<<< orphan*/  rts5260_fill_driving (struct rtsx_pcr*,int) ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rts5260_switch_output_voltage(struct rtsx_pcr *pcr, u8 voltage)
{
	switch (voltage) {
	case OUTPUT_3V3:
		rtsx_pci_write_register(pcr, LDO_CONFIG2,
					DV331812_VDD1, DV331812_VDD1);
		rtsx_pci_write_register(pcr, LDO_DV18_CFG,
					DV331812_MASK, DV331812_33);
		rtsx_pci_write_register(pcr, SD_PAD_CTL, SD_IO_USING_1V8, 0);
		break;
	case OUTPUT_1V8:
		rtsx_pci_write_register(pcr, LDO_CONFIG2,
					DV331812_VDD1, DV331812_VDD1);
		rtsx_pci_write_register(pcr, LDO_DV18_CFG,
					DV331812_MASK, DV331812_17);
		rtsx_pci_write_register(pcr, SD_PAD_CTL, SD_IO_USING_1V8,
					SD_IO_USING_1V8);
		break;
	default:
		return -EINVAL;
	}

	/* set pad drive */
	rts5260_fill_driving(pcr, voltage);

	return 0;
}