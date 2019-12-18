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
struct pm8001_tmf_task {int dummy; } ;
struct pm8001_hba_info {int dummy; } ;
struct pm8001_ccb_info {int dummy; } ;
struct TYPE_2__ {int (* ssp_tm_req ) (struct pm8001_hba_info*,struct pm8001_ccb_info*,struct pm8001_tmf_task*) ;} ;

/* Variables and functions */
 TYPE_1__* PM8001_CHIP_DISP ; 
 int stub1 (struct pm8001_hba_info*,struct pm8001_ccb_info*,struct pm8001_tmf_task*) ; 

__attribute__((used)) static int pm8001_task_prep_ssp_tm(struct pm8001_hba_info *pm8001_ha,
	struct pm8001_ccb_info *ccb, struct pm8001_tmf_task *tmf)
{
	return PM8001_CHIP_DISP->ssp_tm_req(pm8001_ha, ccb, tmf);
}