#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* action; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* fn ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  lgr_info_log () ; 
 TYPE_2__ on_panic_trigger ; 
 int /*<<< orphan*/  stop_run (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void do_panic(void)
{
	lgr_info_log();
	on_panic_trigger.action->fn(&on_panic_trigger);
	stop_run(&on_panic_trigger);
}