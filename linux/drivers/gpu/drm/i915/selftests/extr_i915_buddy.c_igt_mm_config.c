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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  random_seed; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  I915_RND_STATE (int /*<<< orphan*/ ) ; 
 int SZ_8G ; 
 int i915_prandom_u64_state (int /*<<< orphan*/ *) ; 
 TYPE_1__ i915_selftest ; 
 int ilog2 (int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  prandom_seed_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int prandom_u32_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prng ; 

__attribute__((used)) static void igt_mm_config(u64 *size, u64 *chunk_size)
{
	I915_RND_STATE(prng);
	u64 s, ms;

	/* Nothing fancy, just try to get an interesting bit pattern */

	prandom_seed_state(&prng, i915_selftest.random_seed);

	s = i915_prandom_u64_state(&prng) & (SZ_8G - 1);
	ms = BIT_ULL(12 + (prandom_u32_state(&prng) % ilog2(s >> 12)));
	s = max(s & -ms, ms);

	*chunk_size = ms;
	*size = s;
}