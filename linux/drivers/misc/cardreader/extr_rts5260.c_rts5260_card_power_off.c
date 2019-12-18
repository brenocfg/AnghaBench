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
 int /*<<< orphan*/  DV331812_POWEROFF ; 
 int /*<<< orphan*/  DV331812_POWERON ; 
 int /*<<< orphan*/  LDO_CONFIG2 ; 
 int /*<<< orphan*/  LDO_POW_SDVDD1_MASK ; 
 int /*<<< orphan*/  LDO_POW_SDVDD1_OFF ; 
 int /*<<< orphan*/  LDO_VCC_CFG1 ; 
 int /*<<< orphan*/  rts5260_card_before_power_off (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_disable_ocp (struct rtsx_pcr*) ; 
 int rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rts5260_card_power_off(struct rtsx_pcr *pcr, int card)
{
	int err = 0;

	rts5260_card_before_power_off(pcr);
	err = rtsx_pci_write_register(pcr, LDO_VCC_CFG1,
			 LDO_POW_SDVDD1_MASK, LDO_POW_SDVDD1_OFF);
	err = rtsx_pci_write_register(pcr, LDO_CONFIG2,
			 DV331812_POWERON, DV331812_POWEROFF);
	if (pcr->option.ocp_en)
		rtsx_pci_disable_ocp(pcr);

	return err;
}