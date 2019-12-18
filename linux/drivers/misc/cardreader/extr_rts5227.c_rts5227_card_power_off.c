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
struct TYPE_2__ {scalar_t__ ocp_en; } ;
struct rtsx_pcr {TYPE_1__ option; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_PWR_CTL ; 
 int LDO3318_PWR_MASK ; 
 int PMOS_STRG_400mA ; 
 int PMOS_STRG_MASK ; 
 int /*<<< orphan*/  PWR_GATE_CTRL ; 
 int SD_POWER_MASK ; 
 int SD_POWER_OFF ; 
 int /*<<< orphan*/  rtsx_pci_disable_ocp (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int rts5227_card_power_off(struct rtsx_pcr *pcr, int card)
{
	if (pcr->option.ocp_en)
		rtsx_pci_disable_ocp(pcr);

	rtsx_pci_write_register(pcr, CARD_PWR_CTL, SD_POWER_MASK |
			PMOS_STRG_MASK, SD_POWER_OFF | PMOS_STRG_400mA);
	rtsx_pci_write_register(pcr, PWR_GATE_CTRL, LDO3318_PWR_MASK, 0X00);

	return 0;
}