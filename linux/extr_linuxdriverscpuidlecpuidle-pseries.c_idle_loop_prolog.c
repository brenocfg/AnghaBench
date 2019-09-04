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
struct TYPE_2__ {int idle; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_PURR ; 
 TYPE_1__* get_lppaca () ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc64_runlatch_off () ; 

__attribute__((used)) static inline void idle_loop_prolog(unsigned long *in_purr)
{
	ppc64_runlatch_off();
	*in_purr = mfspr(SPRN_PURR);
	/*
	 * Indicate to the HV that we are idle. Now would be
	 * a good time to find other work to dispatch.
	 */
	get_lppaca()->idle = 1;
}