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
 int /*<<< orphan*/  CARD_OE ; 
 int /*<<< orphan*/  CARD_PWR_CTL ; 
 int LDO3318_PWR_MASK ; 
 int MS_OUTPUT_EN ; 
 int /*<<< orphan*/  PWR_GATE_CTRL ; 
 int SD_OUTPUT_EN ; 
 int SD_PARTIAL_POWER_ON ; 
 int SD_POWER_MASK ; 
 int SD_POWER_ON ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtsx_pci_add_cmd (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_pci_enable_ocp (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_init_cmd (struct rtsx_pcr*) ; 
 int rtsx_pci_send_cmd (struct rtsx_pcr*,int) ; 

__attribute__((used)) static int rts5227_card_power_on(struct rtsx_pcr *pcr, int card)
{
	int err;

	if (pcr->option.ocp_en)
		rtsx_pci_enable_ocp(pcr);

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL,
			SD_POWER_MASK, SD_PARTIAL_POWER_ON);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWR_GATE_CTRL,
			LDO3318_PWR_MASK, 0x02);

	err = rtsx_pci_send_cmd(pcr, 100);
	if (err < 0)
		return err;

	/* To avoid too large in-rush current */
	msleep(20);
	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL,
			SD_POWER_MASK, SD_POWER_ON);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PWR_GATE_CTRL,
			LDO3318_PWR_MASK, 0x06);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_OE,
			SD_OUTPUT_EN, SD_OUTPUT_EN);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_OE,
			MS_OUTPUT_EN, MS_OUTPUT_EN);
	return rtsx_pci_send_cmd(pcr, 100);
}