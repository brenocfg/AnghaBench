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
typedef  int u32 ;
typedef  int u16 ;
struct rtsx_cr_option {int ltr_enabled; int ltr_active; int force_clkreq_0; int /*<<< orphan*/  ltr_active_latency; scalar_t__ ltr_en; } ;
struct rtsx_pcr {int /*<<< orphan*/  pci; struct rtsx_cr_option option; } ;

/* Variables and functions */
 int ASPM_L1_1_EN ; 
 int ASPM_L1_1_EN_MASK ; 
 int ASPM_L1_2_EN ; 
 int ASPM_L1_2_EN_MASK ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL2 ; 
 int PCI_EXP_DEVCTL2_LTR_EN ; 
 int /*<<< orphan*/  PCR_ASPM_SETTING_5260 ; 
 int PM_L1_1_EN ; 
 int PM_L1_1_EN_MASK ; 
 int PM_L1_2_EN ; 
 int PM_L1_2_EN_MASK ; 
 int /*<<< orphan*/  pcie_capability_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rts5260_pwr_saving_setting (struct rtsx_pcr*) ; 
 scalar_t__ rtsx_check_dev_flag (struct rtsx_pcr*,int) ; 
 int /*<<< orphan*/  rtsx_pci_read_config_dword (struct rtsx_pcr*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtsx_set_dev_flag (struct rtsx_pcr*,int) ; 
 int /*<<< orphan*/  rtsx_set_ltr_latency (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rts5260_init_from_cfg(struct rtsx_pcr *pcr)
{
	struct rtsx_cr_option *option = &pcr->option;
	u32 lval;

	rtsx_pci_read_config_dword(pcr, PCR_ASPM_SETTING_5260, &lval);

	if (lval & ASPM_L1_1_EN_MASK)
		rtsx_set_dev_flag(pcr, ASPM_L1_1_EN);

	if (lval & ASPM_L1_2_EN_MASK)
		rtsx_set_dev_flag(pcr, ASPM_L1_2_EN);

	if (lval & PM_L1_1_EN_MASK)
		rtsx_set_dev_flag(pcr, PM_L1_1_EN);

	if (lval & PM_L1_2_EN_MASK)
		rtsx_set_dev_flag(pcr, PM_L1_2_EN);

	rts5260_pwr_saving_setting(pcr);

	if (option->ltr_en) {
		u16 val;

		pcie_capability_read_word(pcr->pci, PCI_EXP_DEVCTL2, &val);
		if (val & PCI_EXP_DEVCTL2_LTR_EN) {
			option->ltr_enabled = true;
			option->ltr_active = true;
			rtsx_set_ltr_latency(pcr, option->ltr_active_latency);
		} else {
			option->ltr_enabled = false;
		}
	}

	if (rtsx_check_dev_flag(pcr, ASPM_L1_1_EN | ASPM_L1_2_EN
				| PM_L1_1_EN | PM_L1_2_EN))
		option->force_clkreq_0 = false;
	else
		option->force_clkreq_0 = true;
}