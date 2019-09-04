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
struct powernv_rng {unsigned long mask; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long rng_whiten(struct powernv_rng *rng, unsigned long val)
{
	unsigned long parity;

	/* Calculate the parity of the value */
	asm ("popcntd %0,%1" : "=r" (parity) : "r" (val));

	/* xor our value with the previous mask */
	val ^= rng->mask;

	/* update the mask based on the parity of this value */
	rng->mask = (rng->mask << 1) | (parity & 1);

	return val;
}