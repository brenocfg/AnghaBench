#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ocp_en; int /*<<< orphan*/  sd_800mA_ocp_thd; } ;
struct TYPE_3__ {int /*<<< orphan*/  ocp_glitch; int /*<<< orphan*/  interrupt_en; } ;
struct rtsx_pcr {TYPE_2__ option; TYPE_1__ hw_param; int /*<<< orphan*/  reg_pm_ctrl3; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTS522A_OCP_THD_800 ; 
 int /*<<< orphan*/  RTS522A_PM_CTRL3 ; 
 int /*<<< orphan*/  SD_OCP_GLITCH_10M ; 
 int /*<<< orphan*/  SD_OC_INT_EN ; 
 int /*<<< orphan*/  rts5227_init_params (struct rtsx_pcr*) ; 

void rts522a_init_params(struct rtsx_pcr *pcr)
{
	rts5227_init_params(pcr);

	pcr->reg_pm_ctrl3 = RTS522A_PM_CTRL3;

	pcr->option.ocp_en = 1;
	if (pcr->option.ocp_en)
		pcr->hw_param.interrupt_en |= SD_OC_INT_EN;
	pcr->hw_param.ocp_glitch = SD_OCP_GLITCH_10M;
	pcr->option.sd_800mA_ocp_thd = RTS522A_OCP_THD_800;

}