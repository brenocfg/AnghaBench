#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ltr_l1off_snooze_sspwrgate; int /*<<< orphan*/  ltr_l1off_sspwrgate; } ;
struct rtsx_pcr {int /*<<< orphan*/ * ops; int /*<<< orphan*/  reg_pm_ctrl3; TYPE_1__ option; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTR_L1OFF_SNOOZE_SSPWRGATE_5250_DEF ; 
 int /*<<< orphan*/  LTR_L1OFF_SSPWRGATE_5250_DEF ; 
 int /*<<< orphan*/  RTS524A_PM_CTRL3 ; 
 int /*<<< orphan*/  rts5249_init_params (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rts524a_pcr_ops ; 

void rts524a_init_params(struct rtsx_pcr *pcr)
{
	rts5249_init_params(pcr);
	pcr->option.ltr_l1off_sspwrgate = LTR_L1OFF_SSPWRGATE_5250_DEF;
	pcr->option.ltr_l1off_snooze_sspwrgate =
		LTR_L1OFF_SNOOZE_SSPWRGATE_5250_DEF;

	pcr->reg_pm_ctrl3 = RTS524A_PM_CTRL3;
	pcr->ops = &rts524a_pcr_ops;
}