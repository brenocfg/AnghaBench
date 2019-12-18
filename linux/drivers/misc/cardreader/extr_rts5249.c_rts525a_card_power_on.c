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
 int /*<<< orphan*/  LDO_VCC_3V3 ; 
 int /*<<< orphan*/  LDO_VCC_CFG1 ; 
 int /*<<< orphan*/  LDO_VCC_TUNE_MASK ; 
 int rtsx_base_card_power_on (struct rtsx_pcr*,int) ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rts525a_card_power_on(struct rtsx_pcr *pcr, int card)
{
	rtsx_pci_write_register(pcr, LDO_VCC_CFG1,
		LDO_VCC_TUNE_MASK, LDO_VCC_3V3);
	return rtsx_base_card_power_on(pcr, card);
}