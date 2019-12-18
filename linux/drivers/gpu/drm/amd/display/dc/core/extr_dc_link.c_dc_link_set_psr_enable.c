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
struct dmcu {TYPE_3__* funcs; } ;
struct dc_link {scalar_t__ psr_enabled; TYPE_1__* ctx; } ;
struct dc {TYPE_2__* res_pool; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_psr_enable ) (struct dmcu*,int,int) ;scalar_t__ (* is_dmcu_initialized ) (struct dmcu*) ;} ;
struct TYPE_5__ {struct dmcu* dmcu; } ;
struct TYPE_4__ {struct dc* dc; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct dmcu*) ; 
 int /*<<< orphan*/  stub2 (struct dmcu*,int,int) ; 

bool dc_link_set_psr_enable(const struct dc_link *link, bool enable, bool wait)
{
	struct dc  *core_dc = link->ctx->dc;
	struct dmcu *dmcu = core_dc->res_pool->dmcu;

	if ((dmcu != NULL && dmcu->funcs->is_dmcu_initialized(dmcu)) && link->psr_enabled)
		dmcu->funcs->set_psr_enable(dmcu, enable, wait);

	return true;
}