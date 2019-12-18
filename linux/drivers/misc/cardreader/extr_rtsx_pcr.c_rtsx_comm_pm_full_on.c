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
struct rtsx_cr_option {int /*<<< orphan*/  ltr_active_latency; scalar_t__ ltr_enabled; } ;
struct rtsx_pcr {struct rtsx_cr_option option; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTR_L1SS_PWR_GATE_EN ; 
 scalar_t__ rtsx_check_dev_flag (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_disable_aspm (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_set_l1off_sub_cfg_d0 (struct rtsx_pcr*,int) ; 
 int /*<<< orphan*/  rtsx_set_ltr_latency (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtsx_comm_pm_full_on(struct rtsx_pcr *pcr)
{
	struct rtsx_cr_option *option = &pcr->option;

	rtsx_disable_aspm(pcr);

	if (option->ltr_enabled)
		rtsx_set_ltr_latency(pcr, option->ltr_active_latency);

	if (rtsx_check_dev_flag(pcr, LTR_L1SS_PWR_GATE_EN))
		rtsx_set_l1off_sub_cfg_d0(pcr, 1);
}