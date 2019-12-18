#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* otg; } ;
struct TYPE_8__ {int /*<<< orphan*/  fsm; TYPE_3__ phy; } ;
struct TYPE_6__ {TYPE_1__* host; } ;
struct TYPE_5__ {int /*<<< orphan*/  b_hnp_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDBG (char*) ; 
 int /*<<< orphan*/  a_wait_enum_tmr ; 
 int /*<<< orphan*/  fsl_otg_add_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* fsl_otg_dev ; 
 int /*<<< orphan*/  otg_statemachine (int /*<<< orphan*/ *) ; 

void a_wait_enum(unsigned long foo)
{
	VDBG("a_wait_enum timeout\n");
	if (!fsl_otg_dev->phy.otg->host->b_hnp_enable)
		fsl_otg_add_timer(&fsl_otg_dev->fsm, a_wait_enum_tmr);
	else
		otg_statemachine(&fsl_otg_dev->fsm);
}