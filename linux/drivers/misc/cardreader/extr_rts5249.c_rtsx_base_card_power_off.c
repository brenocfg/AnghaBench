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
struct rtsx_cr_option {scalar_t__ ocp_en; } ;
struct rtsx_pcr {struct rtsx_cr_option option; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_PWR_CTL ; 
 int /*<<< orphan*/  LDO3318_PWR_MASK ; 
 int /*<<< orphan*/  PWR_GATE_CTRL ; 
 int /*<<< orphan*/  SD_POWER_MASK ; 
 int SD_POWER_OFF ; 
 int /*<<< orphan*/  rtsx_pci_disable_ocp (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtsx_base_card_power_off(struct rtsx_pcr *pcr, int card)
{
	struct rtsx_cr_option *option = &pcr->option;

	if (option->ocp_en)
		rtsx_pci_disable_ocp(pcr);

	rtsx_pci_write_register(pcr, CARD_PWR_CTL, SD_POWER_MASK, SD_POWER_OFF);

	rtsx_pci_write_register(pcr, PWR_GATE_CTRL, LDO3318_PWR_MASK, 0x00);
	return 0;
}