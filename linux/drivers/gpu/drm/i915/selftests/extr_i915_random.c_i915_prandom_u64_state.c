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
typedef  int u64 ;
struct rnd_state {int dummy; } ;

/* Variables and functions */
 int prandom_u32_state (struct rnd_state*) ; 

u64 i915_prandom_u64_state(struct rnd_state *rnd)
{
	u64 x;

	x = prandom_u32_state(rnd);
	x <<= 32;
	x |= prandom_u32_state(rnd);

	return x;
}