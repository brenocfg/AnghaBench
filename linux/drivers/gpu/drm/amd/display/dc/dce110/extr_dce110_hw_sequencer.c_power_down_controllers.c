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
struct dc {TYPE_2__* res_pool; } ;
struct TYPE_6__ {TYPE_1__* funcs; } ;
struct TYPE_5__ {int timing_generator_count; TYPE_3__** timing_generators; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable_crtc ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void power_down_controllers(struct dc *dc)
{
	int i;

	for (i = 0; i < dc->res_pool->timing_generator_count; i++) {
		dc->res_pool->timing_generators[i]->funcs->disable_crtc(
				dc->res_pool->timing_generators[i]);
	}
}