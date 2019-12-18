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
struct hubbub {TYPE_4__* funcs; } ;
struct dchub_init_data {int dummy; } ;
struct dce_hwseq {TYPE_3__* ctx; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* update_dchub ) (struct hubbub*,struct dchub_init_data*) ;} ;
struct TYPE_7__ {TYPE_2__* dc; } ;
struct TYPE_6__ {TYPE_1__* res_pool; } ;
struct TYPE_5__ {struct hubbub* hubbub; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hubbub*,struct dchub_init_data*) ; 

__attribute__((used)) static void dcn10_update_dchub(struct dce_hwseq *hws, struct dchub_init_data *dh_data)
{
	struct hubbub *hubbub = hws->ctx->dc->res_pool->hubbub;

	/* In DCN, this programming sequence is owned by the hubbub */
	hubbub->funcs->update_dchub(hubbub, dh_data);
}