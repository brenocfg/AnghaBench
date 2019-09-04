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

void xics_set_cpu_giq(unsigned int gserver, unsigned int join)
{
#ifdef CONFIG_PPC_RTAS
	int index;
	int status;

	if (!rtas_indicator_present(GLOBAL_INTERRUPT_QUEUE, NULL))
		return;

	index = (1UL << xics_interrupt_server_size) - 1 - gserver;

	status = rtas_set_indicator_fast(GLOBAL_INTERRUPT_QUEUE, index, join);

	WARN(status < 0, "set-indicator(%d, %d, %u) returned %d\n",
	     GLOBAL_INTERRUPT_QUEUE, index, join, status);
#endif
}