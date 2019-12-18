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
struct dc {TYPE_1__* res_pool; } ;
struct abm {TYPE_2__* funcs; } ;
struct TYPE_4__ {unsigned int (* get_current_backlight ) (struct abm*) ;} ;
struct TYPE_3__ {struct abm* abm; } ;

/* Variables and functions */
 unsigned int stub1 (struct abm*) ; 

unsigned int dc_get_current_backlight_pwm(struct dc *dc)
{
	struct abm *abm = dc->res_pool->abm;

	if (abm)
		return abm->funcs->get_current_backlight(abm);

	return 0;
}