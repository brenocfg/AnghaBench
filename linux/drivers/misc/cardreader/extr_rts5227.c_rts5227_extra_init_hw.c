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
typedef  int u16 ;
struct rtsx_pcr {int flags; int /*<<< orphan*/  reg_pm_ctrl3; int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPM_FORCE_CTL ; 
 int /*<<< orphan*/  GPIO_CTL ; 
 int /*<<< orphan*/  LDO_PWR_SEL ; 
 int /*<<< orphan*/  LTR_CTL ; 
 int /*<<< orphan*/  OBFF_CFG ; 
 int /*<<< orphan*/  OLT_LED_CTL ; 
 int /*<<< orphan*/  OUTPUT_3V3 ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL2 ; 
 int PCI_EXP_DEVCTL2_LTR_EN ; 
 int PCR_REVERSE_SOCKET ; 
 int /*<<< orphan*/  PETXCFG ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  pcie_capability_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rts5227_fill_driving (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_add_cmd (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_pci_init_cmd (struct rtsx_pcr*) ; 
 int rtsx_pci_send_cmd (struct rtsx_pcr*,int) ; 

__attribute__((used)) static int rts5227_extra_init_hw(struct rtsx_pcr *pcr)
{
	u16 cap;

	rtsx_pci_init_cmd(pcr);

	/* Configure GPIO as output */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, GPIO_CTL, 0x02, 0x02);
	/* Reset ASPM state to default value */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, ASPM_FORCE_CTL, 0x3F, 0);
	/* Switch LDO3318 source from DV33 to card_3v3 */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LDO_PWR_SEL, 0x03, 0x00);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LDO_PWR_SEL, 0x03, 0x01);
	/* LED shine disabled, set initial shine cycle period */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, OLT_LED_CTL, 0x0F, 0x02);
	/* Configure LTR */
	pcie_capability_read_word(pcr->pci, PCI_EXP_DEVCTL2, &cap);
	if (cap & PCI_EXP_DEVCTL2_LTR_EN)
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, LTR_CTL, 0xFF, 0xA3);
	/* Configure OBFF */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, OBFF_CFG, 0x03, 0x03);
	/* Configure driving */
	rts5227_fill_driving(pcr, OUTPUT_3V3);
	/* Configure force_clock_req */
	if (pcr->flags & PCR_REVERSE_SOCKET)
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG, 0xB8, 0xB8);
	else
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PETXCFG, 0xB8, 0x88);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, pcr->reg_pm_ctrl3, 0x10, 0x00);

	return rtsx_pci_send_cmd(pcr, 100);
}