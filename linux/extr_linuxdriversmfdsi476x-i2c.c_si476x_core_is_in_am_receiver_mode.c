#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ func; } ;
struct si476x_core {TYPE_1__ power_up_parameters; } ;

/* Variables and functions */
 scalar_t__ SI476X_FUNC_AM_RECEIVER ; 
 scalar_t__ si476x_core_has_am (struct si476x_core*) ; 

bool si476x_core_is_in_am_receiver_mode(struct si476x_core *core)
{
	return si476x_core_has_am(core) &&
		(core->power_up_parameters.func == SI476X_FUNC_AM_RECEIVER);
}