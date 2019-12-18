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
struct resource_pool {int pipe_count; struct hubp** hubps; } ;
struct hubp {TYPE_1__* funcs; } ;
struct dcn_hubp_state {int /*<<< orphan*/  blank_en; } ;
struct dc {struct resource_pool* res_pool; } ;
struct TYPE_4__ {struct dcn_hubp_state state; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* hubp_clear_underflow ) (struct hubp*) ;int /*<<< orphan*/  (* hubp_read_state ) (struct hubp*) ;} ;

/* Variables and functions */
 TYPE_2__* TO_DCN10_HUBP (struct hubp*) ; 
 int /*<<< orphan*/  stub1 (struct hubp*) ; 
 int /*<<< orphan*/  stub2 (struct hubp*) ; 

__attribute__((used)) static void dcn10_clear_hubp_underflow(struct dc *dc)
{
	struct resource_pool *pool = dc->res_pool;
	int i;

	for (i = 0; i < pool->pipe_count; i++) {
		struct hubp *hubp = pool->hubps[i];
		struct dcn_hubp_state *s = &(TO_DCN10_HUBP(hubp)->state);

		hubp->funcs->hubp_read_state(hubp);

		if (!s->blank_en)
			hubp->funcs->hubp_clear_underflow(hubp);
	}
}