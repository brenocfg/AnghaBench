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
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xics_push_cppr (int /*<<< orphan*/ ) ; 

int xics_retrigger(struct irq_data *data)
{
	/*
	 * We need to push a dummy CPPR when retriggering, since the subsequent
	 * EOI will try to pop it. Passing 0 works, as the function hard codes
	 * the priority value anyway.
	 */
	xics_push_cppr(0);

	/* Tell the core to do a soft retrigger */
	return 0;
}