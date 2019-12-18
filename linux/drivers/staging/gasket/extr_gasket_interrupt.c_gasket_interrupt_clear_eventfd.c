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
struct gasket_interrupt_data {int num_interrupts; int /*<<< orphan*/ ** eventfd_ctxs; } ;

/* Variables and functions */
 int EINVAL ; 

int gasket_interrupt_clear_eventfd(struct gasket_interrupt_data *interrupt_data,
				   int interrupt)
{
	if (interrupt < 0 || interrupt >= interrupt_data->num_interrupts)
		return -EINVAL;

	interrupt_data->eventfd_ctxs[interrupt] = NULL;
	return 0;
}