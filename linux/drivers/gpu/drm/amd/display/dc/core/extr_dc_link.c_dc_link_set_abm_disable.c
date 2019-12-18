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
struct dc_link {TYPE_1__* ctx; } ;
struct dc {TYPE_2__* res_pool; } ;
struct abm {TYPE_3__* funcs; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_abm_immediate_disable ) (struct abm*) ;int /*<<< orphan*/ * set_backlight_level_pwm; } ;
struct TYPE_5__ {struct abm* abm; } ;
struct TYPE_4__ {struct dc* dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct abm*) ; 

bool dc_link_set_abm_disable(const struct dc_link *link)
{
	struct dc  *core_dc = link->ctx->dc;
	struct abm *abm = core_dc->res_pool->abm;

	if ((abm == NULL) || (abm->funcs->set_backlight_level_pwm == NULL))
		return false;

	abm->funcs->set_abm_immediate_disable(abm);

	return true;
}