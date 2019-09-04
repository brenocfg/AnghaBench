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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct kvmppc_xive_src_block {struct kvmppc_xive_irq_state* irq_state; } ;
struct kvmppc_xive_irq_state {int in_queue; int /*<<< orphan*/  saved_p; int /*<<< orphan*/  valid; } ;
struct kvmppc_xive {int dummy; } ;

/* Variables and functions */
 struct kvmppc_xive_src_block* kvmppc_xive_find_source (struct kvmppc_xive*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xive_pre_save_set_queued(struct kvmppc_xive *xive, u32 irq)
{
	struct kvmppc_xive_src_block *sb;
	struct kvmppc_xive_irq_state *state;
	u16 idx;

	sb = kvmppc_xive_find_source(xive, irq, &idx);
	if (!sb)
		return;

	state = &sb->irq_state[idx];

	/* Some sanity checking */
	if (!state->valid) {
		pr_err("invalid irq 0x%x in cpu queue!\n", irq);
		return;
	}

	/*
	 * If the interrupt is in a queue it should have P set.
	 * We warn so that gets reported. A backtrace isn't useful
	 * so no need to use a WARN_ON.
	 */
	if (!state->saved_p)
		pr_err("Interrupt 0x%x is marked in a queue but P not set !\n", irq);

	/* Set flag */
	state->in_queue = true;
}