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
 int /*<<< orphan*/  BPP_LDO_POWB ; 
 int /*<<< orphan*/  BPP_LDO_SUSPEND ; 
 int /*<<< orphan*/  BPP_POWER_MASK ; 
 int /*<<< orphan*/  BPP_POWER_OFF ; 
 int /*<<< orphan*/  CARD_PWR_CTL ; 
 int /*<<< orphan*/  LDO_CTL ; 
 int rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8411_card_power_off(struct rtsx_pcr *pcr, int card)
{
	int err;

	err = rtsx_pci_write_register(pcr, CARD_PWR_CTL,
			BPP_POWER_MASK, BPP_POWER_OFF);
	if (err < 0)
		return err;

	return rtsx_pci_write_register(pcr, LDO_CTL,
			BPP_LDO_POWB, BPP_LDO_SUSPEND);
}