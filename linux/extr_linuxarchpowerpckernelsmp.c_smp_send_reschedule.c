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
 int /*<<< orphan*/  PPC_MSG_RESCHEDULE ; 
 int /*<<< orphan*/  do_message_pass (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_ops ; 

void smp_send_reschedule(int cpu)
{
	if (likely(smp_ops))
		do_message_pass(cpu, PPC_MSG_RESCHEDULE);
}