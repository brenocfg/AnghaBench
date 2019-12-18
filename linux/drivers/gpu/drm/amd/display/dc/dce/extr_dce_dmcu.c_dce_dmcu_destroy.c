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
struct dmcu {int dummy; } ;
struct TYPE_4__ {scalar_t__ dmcu_state; TYPE_1__* funcs; } ;
struct dce_dmcu {TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_psr_enable ) (struct dmcu*,int,int) ;} ;

/* Variables and functions */
 scalar_t__ DMCU_RUNNING ; 
 struct dce_dmcu* TO_DCE_DMCU (struct dmcu*) ; 
 int /*<<< orphan*/  kfree (struct dce_dmcu*) ; 
 int /*<<< orphan*/  stub1 (struct dmcu*,int,int) ; 

void dce_dmcu_destroy(struct dmcu **dmcu)
{
	struct dce_dmcu *dmcu_dce = TO_DCE_DMCU(*dmcu);

	if (dmcu_dce->base.dmcu_state == DMCU_RUNNING)
		dmcu_dce->base.funcs->set_psr_enable(*dmcu, false, true);

	kfree(dmcu_dce);
	*dmcu = NULL;
}