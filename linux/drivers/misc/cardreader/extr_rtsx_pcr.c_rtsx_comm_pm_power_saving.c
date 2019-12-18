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
typedef  int /*<<< orphan*/  u32 ;
struct rtsx_cr_option {int /*<<< orphan*/  l1_snooze_delay; int /*<<< orphan*/  ltr_l1off_latency; scalar_t__ ltr_enabled; } ;
struct rtsx_pcr {struct rtsx_cr_option option; } ;

/* Variables and functions */
 int /*<<< orphan*/  L1_SNOOZE_TEST_EN ; 
 int /*<<< orphan*/  LTR_L1SS_PWR_GATE_EN ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 scalar_t__ rtsx_check_dev_flag (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_enable_aspm (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_set_l1off_sub_cfg_d0 (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_set_ltr_latency (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtsx_comm_pm_power_saving(struct rtsx_pcr *pcr)
{
	struct rtsx_cr_option *option = &pcr->option;

	if (option->ltr_enabled) {
		u32 latency = option->ltr_l1off_latency;

		if (rtsx_check_dev_flag(pcr, L1_SNOOZE_TEST_EN))
			mdelay(option->l1_snooze_delay);

		rtsx_set_ltr_latency(pcr, latency);
	}

	if (rtsx_check_dev_flag(pcr, LTR_L1SS_PWR_GATE_EN))
		rtsx_set_l1off_sub_cfg_d0(pcr, 0);

	rtsx_enable_aspm(pcr);
}