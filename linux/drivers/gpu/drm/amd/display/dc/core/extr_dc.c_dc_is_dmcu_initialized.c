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
struct dmcu {TYPE_2__* funcs; } ;
struct dc {TYPE_1__* res_pool; } ;
struct TYPE_4__ {int (* is_dmcu_initialized ) (struct dmcu*) ;} ;
struct TYPE_3__ {struct dmcu* dmcu; } ;

/* Variables and functions */
 int stub1 (struct dmcu*) ; 

bool dc_is_dmcu_initialized(struct dc *dc)
{
	struct dmcu *dmcu = dc->res_pool->dmcu;

	if (dmcu)
		return dmcu->funcs->is_dmcu_initialized(dmcu);
	return false;
}