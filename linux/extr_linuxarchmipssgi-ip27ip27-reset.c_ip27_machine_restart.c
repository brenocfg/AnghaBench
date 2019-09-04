#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  LOCAL_HUB_S (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NI_PORT_RESET ; 
 int NPR_LOCALRESET ; 
 int NPR_PORTRESET ; 
 int /*<<< orphan*/  noreturn ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void ip27_machine_restart(char *command)
{
#if 0
	int i;
#endif

	printk("Reboot started from CPU %d\n", smp_processor_id());
#ifdef CONFIG_SMP
	smp_send_stop();
#endif
#if 0
	for_each_online_node(i)
		REMOTE_HUB_S(COMPACT_TO_NASID_NODEID(i), PROMOP_REG,
							PROMOP_REBOOT);
#else
	LOCAL_HUB_S(NI_PORT_RESET, NPR_PORTRESET | NPR_LOCALRESET);
#endif
	noreturn;
}