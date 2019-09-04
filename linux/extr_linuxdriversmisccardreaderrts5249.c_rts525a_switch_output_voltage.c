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
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LDO_CONFIG2 ; 
 int /*<<< orphan*/  LDO_D3318_18V ; 
 int /*<<< orphan*/  LDO_D3318_33V ; 
 int /*<<< orphan*/  LDO_D3318_MASK ; 
#define  OUTPUT_1V8 129 
#define  OUTPUT_3V3 128 
 int /*<<< orphan*/  SD_IO_USING_1V8 ; 
 int /*<<< orphan*/  SD_PAD_CTL ; 
 int /*<<< orphan*/  rts5249_fill_driving (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_init_cmd (struct rtsx_pcr*) ; 
 int rtsx_pci_send_cmd (struct rtsx_pcr*,int) ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rts525a_switch_output_voltage(struct rtsx_pcr *pcr, u8 voltage)
{
	switch (voltage) {
	case OUTPUT_3V3:
		rtsx_pci_write_register(pcr, LDO_CONFIG2,
			LDO_D3318_MASK, LDO_D3318_33V);
		rtsx_pci_write_register(pcr, SD_PAD_CTL, SD_IO_USING_1V8, 0);
		break;
	case OUTPUT_1V8:
		rtsx_pci_write_register(pcr, LDO_CONFIG2,
			LDO_D3318_MASK, LDO_D3318_18V);
		rtsx_pci_write_register(pcr, SD_PAD_CTL, SD_IO_USING_1V8,
			SD_IO_USING_1V8);
		break;
	default:
		return -EINVAL;
	}

	rtsx_pci_init_cmd(pcr);
	rts5249_fill_driving(pcr, voltage);
	return rtsx_pci_send_cmd(pcr, 100);
}