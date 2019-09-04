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
struct dchub_init_data {int dummy; } ;
struct dce_hwseq {TYPE_2__* ctx; } ;
struct TYPE_8__ {int /*<<< orphan*/ * hubbub; struct hubp** hubps; } ;
struct TYPE_7__ {TYPE_4__* res_pool; } ;
struct TYPE_6__ {TYPE_3__* dc; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* hubp_update_dchub ) (struct hubp*,struct dchub_init_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hubbub1_update_dchub (int /*<<< orphan*/ *,struct dchub_init_data*) ; 
 int /*<<< orphan*/  stub1 (struct hubp*,struct dchub_init_data*) ; 

__attribute__((used)) static void dcn10_update_dchub(struct dce_hwseq *hws, struct dchub_init_data *dh_data)
{
	if (hws->ctx->dc->res_pool->hubbub != NULL) {
		struct hubp *hubp = hws->ctx->dc->res_pool->hubps[0];

		if (hubp->funcs->hubp_update_dchub)
			hubp->funcs->hubp_update_dchub(hubp, dh_data);
		else
			hubbub1_update_dchub(hws->ctx->dc->res_pool->hubbub, dh_data);
	}
}