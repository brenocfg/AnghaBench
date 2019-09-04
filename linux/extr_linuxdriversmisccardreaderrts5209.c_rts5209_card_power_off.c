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
struct rtsx_pcr {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_PWR_CTL ; 
 int LDO3318_PWR_MASK ; 
 int MS_POWER_MASK ; 
 int MS_POWER_OFF ; 
 int PCR_MS_PMOS ; 
 int PMOS_STRG_400mA ; 
 int PMOS_STRG_MASK ; 
 int /*<<< orphan*/  PWR_GATE_CTRL ; 
 int RTSX_MS_CARD ; 
 int SD_POWER_MASK ; 
 int SD_POWER_OFF ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  rtsx_pci_add_cmd (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_pci_init_cmd (struct rtsx_pcr*) ; 
 int rtsx_pci_send_cmd (struct rtsx_pcr*,int) ; 

__attribute__((used)) static int rts5209_card_power_off(struct rtsx_pcr *pcr, int card)
{
	u8 pwr_mask, pwr_off;

	pwr_mask = SD_POWER_MASK;
	pwr_off = SD_POWER_OFF;

	if ((pcr->flags & PCR_MS_PMOS) && (card == RTSX_MS_CARD)) {
		pwr_mask = MS_POWER_MASK;
		pwr_off = MS_POWER_OFF;
	}

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL,
			pwr_mask | PMOS_STRG_MASK, pwr_off | PMOS_STRG_400mA);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWR_GATE_CTRL,
			LDO3318_PWR_MASK, 0x06);
	return rtsx_pci_send_cmd(pcr, 100);
}