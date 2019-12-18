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
struct TYPE_4__ {TYPE_1__* telem_ops; } ;
struct TYPE_3__ {int (* reset_events ) () ;} ;

/* Variables and functions */
 int stub1 () ; 
 TYPE_2__ telm_core_conf ; 

int telemetry_reset_events(void)
{
	return telm_core_conf.telem_ops->reset_events();
}