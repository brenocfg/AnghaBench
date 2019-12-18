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
struct TYPE_2__ {int /*<<< orphan*/  conn_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCONNECTED ; 
 int /*<<< orphan*/  cpuhp_remove_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_stimer_global_cleanup () ; 
 int /*<<< orphan*/  hyperv_cleanup () ; 
 int /*<<< orphan*/  hyperv_cpuhp_online ; 
 int /*<<< orphan*/  mb () ; 
 TYPE_1__ vmbus_connection ; 
 int /*<<< orphan*/  vmbus_initiate_unload (int) ; 

__attribute__((used)) static void hv_kexec_handler(void)
{
	hv_stimer_global_cleanup();
	vmbus_initiate_unload(false);
	vmbus_connection.conn_state = DISCONNECTED;
	/* Make sure conn_state is set as hv_synic_cleanup checks for it */
	mb();
	cpuhp_remove_state(hyperv_cpuhp_online);
	hyperv_cleanup();
}