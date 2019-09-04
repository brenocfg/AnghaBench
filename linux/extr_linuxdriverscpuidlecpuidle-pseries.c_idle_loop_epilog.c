#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ idle; int /*<<< orphan*/  wait_state_cycles; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_PURR ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_lppaca () ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc64_runlatch_on () ; 

__attribute__((used)) static inline void idle_loop_epilog(unsigned long in_purr)
{
	u64 wait_cycles;

	wait_cycles = be64_to_cpu(get_lppaca()->wait_state_cycles);
	wait_cycles += mfspr(SPRN_PURR) - in_purr;
	get_lppaca()->wait_state_cycles = cpu_to_be64(wait_cycles);
	get_lppaca()->idle = 0;

	ppc64_runlatch_on();
}