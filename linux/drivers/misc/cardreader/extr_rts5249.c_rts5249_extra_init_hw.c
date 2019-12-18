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
struct rtsx_cr_option {scalar_t__ force_clkreq_0; } ;
struct rtsx_pcr {int flags; struct rtsx_cr_option option; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPM_FORCE_CTL ; 
 int /*<<< orphan*/  CMD_TIMEOUT_DEF ; 
 int FORCE_CLKREQ_DELINK_MASK ; 
 int FORCE_CLKREQ_HIGH ; 
 int FORCE_CLKREQ_LOW ; 
 int /*<<< orphan*/  GPIO_CTL ; 
 int /*<<< orphan*/  L1SUB_CONFIG3 ; 
 int /*<<< orphan*/  LDO_PWR_SEL ; 
 int /*<<< orphan*/  OLT_LED_CTL ; 
 int /*<<< orphan*/  OUTPUT_3V3 ; 
 int PCR_REVERSE_SOCKET ; 
 int /*<<< orphan*/  PETXCFG ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  rts5249_fill_driving (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rts5249_init_from_cfg (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rts5249_init_from_hw (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_add_cmd (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_pci_init_cmd (struct rtsx_pcr*) ; 
 int rtsx_pci_send_cmd (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rts5249_extra_init_hw(struct rtsx_pcr *pcr)
{
	struct rtsx_cr_option *option = &(pcr->option);

	rts5249_init_from_cfg(pcr);
	rts5249_init_from_hw(pcr);

	rtsx_pci_init_cmd(pcr);

	/* Rest L1SUB Config */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, L1SUB_CONFIG3, 0xFF, 0x00);
	/* Configure GPIO as output */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, GPIO_CTL, 0x02, 0x02);
	/* Reset ASPM state to default value */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, ASPM_FORCE_CTL, 0x3F, 0);
	/* Switch LDO3318 source from DV33 to card_3v3 */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LDO_PWR_SEL, 0x03, 0x00);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LDO_PWR_SEL, 0x03, 0x01);
	/* LED shine disabled, set initial shine cycle period */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, OLT_LED_CTL, 0x0F, 0x02);
	/* Configure driving */
	rts5249_fill_driving(pcr, OUTPUT_3V3);
	if (pcr->flags & PCR_REVERSE_SOCKET)
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG, 0xB0, 0xB0);
	else
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG, 0xB0, 0x80);

	/*
	 * If u_force_clkreq_0 is enabled, CLKREQ# PIN will be forced
	 * to drive low, and we forcibly request clock.
	 */
	if (option->force_clkreq_0)
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG,
			FORCE_CLKREQ_DELINK_MASK, FORCE_CLKREQ_LOW);
	else
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG,
			FORCE_CLKREQ_DELINK_MASK, FORCE_CLKREQ_HIGH);

	return rtsx_pci_send_cmd(pcr, CMD_TIMEOUT_DEF);
}