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
struct TYPE_4__ {int dmcu_is_running; TYPE_1__* funcs; } ;
struct dce_abm {TYPE_2__ base; } ;
struct abm {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_abm_immediate_disable ) (struct abm*) ;} ;

/* Variables and functions */
 struct dce_abm* TO_DCE_ABM (struct abm*) ; 
 int /*<<< orphan*/  kfree (struct dce_abm*) ; 
 int /*<<< orphan*/  stub1 (struct abm*) ; 

void dce_abm_destroy(struct abm **abm)
{
	struct dce_abm *abm_dce = TO_DCE_ABM(*abm);

	if (abm_dce->base.dmcu_is_running == true)
		abm_dce->base.funcs->set_abm_immediate_disable(*abm);

	kfree(abm_dce);
	*abm = NULL;
}