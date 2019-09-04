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
 int /*<<< orphan*/  BPP_LDO_ON ; 
 int /*<<< orphan*/  BPP_LDO_POWB ; 
 int /*<<< orphan*/  BPP_LDO_SUSPEND ; 
 int /*<<< orphan*/  BPP_POWER_10_PERCENT_ON ; 
 int /*<<< orphan*/  BPP_POWER_15_PERCENT_ON ; 
 int /*<<< orphan*/  BPP_POWER_5_PERCENT_ON ; 
 int /*<<< orphan*/  BPP_POWER_MASK ; 
 int /*<<< orphan*/  BPP_POWER_ON ; 
 int /*<<< orphan*/  CARD_PWR_CTL ; 
 int /*<<< orphan*/  LDO_CTL ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  rtsx_pci_add_cmd (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_init_cmd (struct rtsx_pcr*) ; 
 int rtsx_pci_send_cmd (struct rtsx_pcr*,int) ; 
 int rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rtl8411_card_power_on(struct rtsx_pcr *pcr, int card)
{
	int err;

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_PWR_CTL,
			BPP_POWER_MASK, BPP_POWER_5_PERCENT_ON);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LDO_CTL,
			BPP_LDO_POWB, BPP_LDO_SUSPEND);
	err = rtsx_pci_send_cmd(pcr, 100);
	if (err < 0)
		return err;

	/* To avoid too large in-rush current */
	udelay(150);

	err = rtsx_pci_write_register(pcr, CARD_PWR_CTL,
			BPP_POWER_MASK, BPP_POWER_10_PERCENT_ON);
	if (err < 0)
		return err;

	udelay(150);

	err = rtsx_pci_write_register(pcr, CARD_PWR_CTL,
			BPP_POWER_MASK, BPP_POWER_15_PERCENT_ON);
	if (err < 0)
		return err;

	udelay(150);

	err = rtsx_pci_write_register(pcr, CARD_PWR_CTL,
			BPP_POWER_MASK, BPP_POWER_ON);
	if (err < 0)
		return err;

	return rtsx_pci_write_register(pcr, LDO_CTL, BPP_LDO_POWB, BPP_LDO_ON);
}