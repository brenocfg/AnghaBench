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
struct TYPE_2__ {int /*<<< orphan*/ * vddc_dep_on_dal_pwrl; } ;
struct pp_hwmgr {int /*<<< orphan*/ * backend; TYPE_1__ dyn_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vega10_hwmgr_backend_fini(struct pp_hwmgr *hwmgr)
{
	kfree(hwmgr->dyn_state.vddc_dep_on_dal_pwrl);
	hwmgr->dyn_state.vddc_dep_on_dal_pwrl = NULL;

	kfree(hwmgr->backend);
	hwmgr->backend = NULL;

	return 0;
}