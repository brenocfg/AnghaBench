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
struct alt_region {struct alt_instr* end; struct alt_instr* begin; } ;
struct alt_instr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ __alt_instructions ; 
 scalar_t__ __alt_instructions_end ; 
 int /*<<< orphan*/  __apply_alternatives (struct alt_region*,int) ; 
 int /*<<< orphan*/  alternatives_applied ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  isb () ; 
 scalar_t__ smp_processor_id () ; 

__attribute__((used)) static int __apply_alternatives_multi_stop(void *unused)
{
	struct alt_region region = {
		.begin	= (struct alt_instr *)__alt_instructions,
		.end	= (struct alt_instr *)__alt_instructions_end,
	};

	/* We always have a CPU 0 at this point (__init) */
	if (smp_processor_id()) {
		while (!READ_ONCE(alternatives_applied))
			cpu_relax();
		isb();
	} else {
		BUG_ON(alternatives_applied);
		__apply_alternatives(&region, false);
		/* Barriers provided by the cache flushing */
		WRITE_ONCE(alternatives_applied, 1);
	}

	return 0;
}