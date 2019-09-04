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
struct ipmi_smi {int /*<<< orphan*/  recv_tasklet; int /*<<< orphan*/  watchdog_pretimeouts_to_deliver; scalar_t__ in_shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void ipmi_smi_watchdog_pretimeout(struct ipmi_smi *intf)
{
	if (intf->in_shutdown)
		return;

	atomic_set(&intf->watchdog_pretimeouts_to_deliver, 1);
	tasklet_schedule(&intf->recv_tasklet);
}