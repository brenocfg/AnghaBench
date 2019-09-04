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
struct octeon_cop2_state {int dummy; } ;

/* Variables and functions */
 unsigned long ST0_CU2 ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  octeon_cop2_restore (struct octeon_cop2_state*) ; 
 int /*<<< orphan*/  preempt_enable () ; 
 unsigned long read_c0_status () ; 
 int /*<<< orphan*/  write_c0_status (unsigned long) ; 

void octeon_crypto_disable(struct octeon_cop2_state *state,
			   unsigned long crypto_flags)
{
	unsigned long flags;

	local_irq_save(flags);
	if (crypto_flags & ST0_CU2)
		octeon_cop2_restore(state);
	else
		write_c0_status(read_c0_status() & ~ST0_CU2);
	local_irq_restore(flags);
	preempt_enable();
}