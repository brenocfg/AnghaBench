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
struct TYPE_2__ {int /*<<< orphan*/  (* restart ) (char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  do_kernel_restart (char*) ; 
 int /*<<< orphan*/  machine_hang () ; 
 int /*<<< orphan*/  machine_shutdown () ; 
 int /*<<< orphan*/  mdelay (int) ; 
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  smp_send_stop () ; 
 int /*<<< orphan*/  stub1 (char*) ; 

void machine_restart(char *cmd)
{
	machine_shutdown();
	if (ppc_md.restart)
		ppc_md.restart(cmd);

	smp_send_stop();

	do_kernel_restart(cmd);
	mdelay(1000);

	machine_hang();
}