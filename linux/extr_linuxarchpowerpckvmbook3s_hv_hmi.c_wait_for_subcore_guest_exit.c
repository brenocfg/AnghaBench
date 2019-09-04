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
struct TYPE_4__ {TYPE_1__* sibling_subcore_state; } ;
struct TYPE_3__ {scalar_t__* in_guest; } ;

/* Variables and functions */
 int MAX_SUBCORE_PER_CORE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_2__* local_paca ; 

void wait_for_subcore_guest_exit(void)
{
	int i;

	/*
	 * NULL bitmap pointer indicates that KVM module hasn't
	 * been loaded yet and hence no guests are running.
	 * If no KVM is in use, no need to co-ordinate among threads
	 * as all of them will always be in host and no one is going
	 * to modify TB other than the opal hmi handler.
	 * Hence, just return from here.
	 */
	if (!local_paca->sibling_subcore_state)
		return;

	for (i = 0; i < MAX_SUBCORE_PER_CORE; i++)
		while (local_paca->sibling_subcore_state->in_guest[i])
			cpu_relax();
}