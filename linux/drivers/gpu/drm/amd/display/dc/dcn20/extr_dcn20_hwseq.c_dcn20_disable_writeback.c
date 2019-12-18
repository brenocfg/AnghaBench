#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mcif_wb {TYPE_3__* funcs; } ;
struct dwbc {TYPE_2__* funcs; } ;
struct dc {TYPE_1__* res_pool; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* disable_mcif ) (struct mcif_wb*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* disable ) (struct dwbc*) ;} ;
struct TYPE_4__ {struct mcif_wb** mcif_wb; struct dwbc** dwbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned int MAX_DWB_PIPES ; 
 int /*<<< orphan*/  stub1 (struct dwbc*) ; 
 int /*<<< orphan*/  stub2 (struct mcif_wb*) ; 

void dcn20_disable_writeback(
		struct dc *dc,
		unsigned int dwb_pipe_inst)
{
	struct dwbc *dwb;
	struct mcif_wb *mcif_wb;

	ASSERT(dwb_pipe_inst < MAX_DWB_PIPES);
	dwb = dc->res_pool->dwbc[dwb_pipe_inst];
	mcif_wb = dc->res_pool->mcif_wb[dwb_pipe_inst];

	dwb->funcs->disable(dwb);
	mcif_wb->funcs->disable_mcif(mcif_wb);
}