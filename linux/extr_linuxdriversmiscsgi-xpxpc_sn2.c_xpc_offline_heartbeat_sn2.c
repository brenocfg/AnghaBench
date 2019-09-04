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
struct TYPE_2__ {int heartbeat_offline; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpc_increment_heartbeat_sn2 () ; 
 TYPE_1__* xpc_vars_sn2 ; 

__attribute__((used)) static void
xpc_offline_heartbeat_sn2(void)
{
	xpc_increment_heartbeat_sn2();
	xpc_vars_sn2->heartbeat_offline = 1;
}