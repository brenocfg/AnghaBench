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
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TIMEOUT_DEF ; 
 int /*<<< orphan*/  DV331812_POWEROFF ; 
 int /*<<< orphan*/  DV331812_POWERON ; 
 int /*<<< orphan*/  LDO_CONFIG2 ; 
 int /*<<< orphan*/  LDO_POW_SDVDD1_MASK ; 
 int /*<<< orphan*/  LDO_POW_SDVDD1_OFF ; 
 int /*<<< orphan*/  LDO_VCC_CFG1 ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  rts5260_card_before_power_off (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_add_cmd (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_init_cmd (struct rtsx_pcr*) ; 
 int rtsx_pci_send_cmd (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rts5260_card_power_off(struct rtsx_pcr *pcr, int card)
{
	int err = 0;

	rts5260_card_before_power_off(pcr);

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LDO_VCC_CFG1,
			 LDO_POW_SDVDD1_MASK, LDO_POW_SDVDD1_OFF);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LDO_CONFIG2,
			 DV331812_POWERON, DV331812_POWEROFF);
	err = rtsx_pci_send_cmd(pcr, CMD_TIMEOUT_DEF);

	return err;
}