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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rtsx_cr_option {int /*<<< orphan*/  ltr_l1off_sspwrgate; int /*<<< orphan*/  ltr_l1off_snooze_sspwrgate; } ;
struct rtsx_pcr {struct rtsx_cr_option option; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPM_L1_1_EN ; 
 int /*<<< orphan*/  ASPM_L1_2_EN ; 
 int /*<<< orphan*/  L1OFF_MBIAS2_EN_5250 ; 
 int /*<<< orphan*/  LTR_L1SS_PWR_GATE_CHECK_CARD_EN ; 
 int MS_EXIST ; 
 int /*<<< orphan*/  RTSX_BIPR ; 
 int SD_EXIST ; 
 int rtsx_check_dev_flag (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int rtsx_pci_readl (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_set_l1off_sub (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rts5250_set_l1off_cfg_sub_d0(struct rtsx_pcr *pcr, int active)
{
	struct rtsx_cr_option *option = &(pcr->option);

	u32 interrupt = rtsx_pci_readl(pcr, RTSX_BIPR);
	int card_exist = (interrupt & SD_EXIST) | (interrupt & MS_EXIST);
	int aspm_L1_1, aspm_L1_2;
	u8 val = 0;

	aspm_L1_1 = rtsx_check_dev_flag(pcr, ASPM_L1_1_EN);
	aspm_L1_2 = rtsx_check_dev_flag(pcr, ASPM_L1_2_EN);

	if (active) {
		/* Run, latency: 60us */
		if (aspm_L1_1)
			val = option->ltr_l1off_snooze_sspwrgate;
	} else {
		/* L1off, latency: 300us */
		if (aspm_L1_2)
			val = option->ltr_l1off_sspwrgate;
	}

	if (aspm_L1_1 || aspm_L1_2) {
		if (rtsx_check_dev_flag(pcr,
					LTR_L1SS_PWR_GATE_CHECK_CARD_EN)) {
			if (card_exist)
				val &= ~L1OFF_MBIAS2_EN_5250;
			else
				val |= L1OFF_MBIAS2_EN_5250;
		}
	}
	rtsx_set_l1off_sub(pcr, val);
}