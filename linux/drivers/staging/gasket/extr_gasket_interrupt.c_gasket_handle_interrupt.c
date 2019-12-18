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
struct gasket_interrupt_data {int /*<<< orphan*/ * interrupt_counts; struct eventfd_ctx** eventfd_ctxs; int /*<<< orphan*/  name; } ;
struct eventfd_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eventfd_signal (struct eventfd_ctx*,int) ; 
 int /*<<< orphan*/  trace_gasket_interrupt_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gasket_handle_interrupt(struct gasket_interrupt_data *interrupt_data,
			int interrupt_index)
{
	struct eventfd_ctx *ctx;

	trace_gasket_interrupt_event(interrupt_data->name, interrupt_index);
	ctx = interrupt_data->eventfd_ctxs[interrupt_index];
	if (ctx)
		eventfd_signal(ctx, 1);

	++(interrupt_data->interrupt_counts[interrupt_index]);
}