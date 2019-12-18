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

/* Variables and functions */
 int /*<<< orphan*/  i915_prandom_shuffle (unsigned int*,int,unsigned int,struct rnd_state*) ; 

void i915_random_reorder(unsigned int *order, unsigned int count,
			 struct rnd_state *state)
{
	i915_prandom_shuffle(order, sizeof(*order), count, state);
}