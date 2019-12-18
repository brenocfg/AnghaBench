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
struct rtsx_cr_option {int force_clkreq_0; } ;
struct rtsx_pcr {struct rtsx_cr_option option; } ;

/* Variables and functions */
 int ASPM_L1_1_EN ; 
 int ASPM_L1_2_EN ; 
 int PM_L1_1_EN ; 
 int PM_L1_2_EN ; 
 scalar_t__ rtsx_check_dev_flag (struct rtsx_pcr*,int) ; 

__attribute__((used)) static int rts5249_init_from_hw(struct rtsx_pcr *pcr)
{
	struct rtsx_cr_option *option = &(pcr->option);

	if (rtsx_check_dev_flag(pcr, ASPM_L1_1_EN | ASPM_L1_2_EN
				| PM_L1_1_EN | PM_L1_2_EN))
		option->force_clkreq_0 = false;
	else
		option->force_clkreq_0 = true;

	return 0;
}