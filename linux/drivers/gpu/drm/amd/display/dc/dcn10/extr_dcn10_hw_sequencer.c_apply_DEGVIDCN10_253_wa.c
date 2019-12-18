#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct hubp {TYPE_5__* funcs; int /*<<< orphan*/  power_gated; } ;
struct TYPE_12__ {int DEGVIDCN10_253_applied; } ;
struct TYPE_8__ {int /*<<< orphan*/  DEGVIDCN10_253; } ;
struct dce_hwseq {TYPE_6__ wa_state; TYPE_2__ wa; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* hubp_pg_control ) (struct dce_hwseq*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_7__ {scalar_t__ disable_stutter; } ;
struct dc {TYPE_4__ hwss; TYPE_3__* res_pool; TYPE_1__ debug; struct dce_hwseq* hwseq; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* set_hubp_blank_en ) (struct hubp*,int) ;} ;
struct TYPE_9__ {int pipe_count; struct hubp** hubps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_IP_REQUEST_CNTL ; 
 int /*<<< orphan*/  IP_REQUEST_EN ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dce_hwseq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct hubp*,int) ; 

__attribute__((used)) static void apply_DEGVIDCN10_253_wa(struct dc *dc)
{
	struct dce_hwseq *hws = dc->hwseq;
	struct hubp *hubp = dc->res_pool->hubps[0];
	int i;

	if (dc->debug.disable_stutter)
		return;

	if (!hws->wa.DEGVIDCN10_253)
		return;

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		if (!dc->res_pool->hubps[i]->power_gated)
			return;
	}

	/* all pipe power gated, apply work around to enable stutter. */

	REG_SET(DC_IP_REQUEST_CNTL, 0,
			IP_REQUEST_EN, 1);

	dc->hwss.hubp_pg_control(hws, 0, true);
	REG_SET(DC_IP_REQUEST_CNTL, 0,
			IP_REQUEST_EN, 0);

	hubp->funcs->set_hubp_blank_en(hubp, false);
	hws->wa_state.DEGVIDCN10_253_applied = true;
}