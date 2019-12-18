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
struct hubp {TYPE_1__* funcs; } ;
struct TYPE_8__ {int DEGVIDCN10_253_applied; } ;
struct dce_hwseq {TYPE_4__ wa_state; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* hubp_pg_control ) (struct dce_hwseq*,int /*<<< orphan*/ ,int) ;} ;
struct dc {TYPE_2__ hwss; TYPE_3__* res_pool; struct dce_hwseq* hwseq; } ;
struct TYPE_7__ {struct hubp** hubps; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_blank ) (struct hubp*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DC_IP_REQUEST_CNTL ; 
 int /*<<< orphan*/  IP_REQUEST_EN ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct hubp*,int) ; 
 int /*<<< orphan*/  stub2 (struct dce_hwseq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void undo_DEGVIDCN10_253_wa(struct dc *dc)
{
	struct dce_hwseq *hws = dc->hwseq;
	struct hubp *hubp = dc->res_pool->hubps[0];

	if (!hws->wa_state.DEGVIDCN10_253_applied)
		return;

	hubp->funcs->set_blank(hubp, true);

	REG_SET(DC_IP_REQUEST_CNTL, 0,
			IP_REQUEST_EN, 1);

	dc->hwss.hubp_pg_control(hws, 0, false);
	REG_SET(DC_IP_REQUEST_CNTL, 0,
			IP_REQUEST_EN, 0);

	hws->wa_state.DEGVIDCN10_253_applied = false;
}