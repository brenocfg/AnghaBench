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
struct TYPE_2__ {struct dc_context* ctx; } ;
struct pp_smu_funcs_rv {int /*<<< orphan*/  set_pme_wa_enable; int /*<<< orphan*/  set_wm_ranges; int /*<<< orphan*/  set_display_requirement; TYPE_1__ pp_smu; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pp_rv_set_display_requirement ; 
 int /*<<< orphan*/  pp_rv_set_pme_wa_enable ; 
 int /*<<< orphan*/  pp_rv_set_wm_ranges ; 

void dm_pp_get_funcs_rv(
		struct dc_context *ctx,
		struct pp_smu_funcs_rv *funcs)
{
	funcs->pp_smu.ctx = ctx;
	funcs->set_display_requirement = pp_rv_set_display_requirement;
	funcs->set_wm_ranges = pp_rv_set_wm_ranges;
	funcs->set_pme_wa_enable = pp_rv_set_pme_wa_enable;
}