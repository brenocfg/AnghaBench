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
struct rnd_state {int dummy; } ;
typedef  int /*<<< orphan*/  stack ;

/* Variables and functions */
 size_t U32_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 size_t i915_prandom_u32_max_state (size_t,struct rnd_state*) ; 
 int /*<<< orphan*/  memcpy (void*,char*,size_t) ; 

void i915_prandom_shuffle(void *arr, size_t elsz, size_t count,
			  struct rnd_state *state)
{
	char stack[128];

	if (WARN_ON(elsz > sizeof(stack) || count > U32_MAX))
		return;

	if (!elsz || !count)
		return;

	/* Fisher-Yates shuffle courtesy of Knuth */
	while (--count) {
		size_t swp;

		swp = i915_prandom_u32_max_state(count + 1, state);
		if (swp == count)
			continue;

		memcpy(stack, arr + count * elsz, elsz);
		memcpy(arr + count * elsz, arr + swp * elsz, elsz);
		memcpy(arr + swp * elsz, stack, elsz);
	}
}