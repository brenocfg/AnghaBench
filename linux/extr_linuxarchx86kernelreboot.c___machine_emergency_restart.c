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
struct TYPE_2__ {int /*<<< orphan*/  (* emergency_restart ) () ;} ;

/* Variables and functions */
 TYPE_1__ machine_ops ; 
 int reboot_emergency ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void __machine_emergency_restart(int emergency)
{
	reboot_emergency = emergency;
	machine_ops.emergency_restart();
}