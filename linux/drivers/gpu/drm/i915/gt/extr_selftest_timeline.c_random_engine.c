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
 int /*<<< orphan*/  I915_NUM_ENGINES ; 
 unsigned int i915_prandom_u32_max_state (int /*<<< orphan*/ ,struct rnd_state*) ; 

__attribute__((used)) static unsigned int random_engine(struct rnd_state *rnd)
{
	return i915_prandom_u32_max_state(I915_NUM_ENGINES, rnd);
}