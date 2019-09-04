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
struct TYPE_2__ {int /*<<< orphan*/  (* heartbeat_exit ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_1__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_hb_timer ; 

__attribute__((used)) static void
xpc_stop_hb_beater(void)
{
	del_timer_sync(&xpc_hb_timer);
	xpc_arch_ops.heartbeat_exit();
}