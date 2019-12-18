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

/* Variables and functions */
 unsigned int CACHELINE_BYTES ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned int) ; 

__attribute__((used)) static inline unsigned int
__intel_ring_space(unsigned int head, unsigned int tail, unsigned int size)
{
	/*
	 * "If the Ring Buffer Head Pointer and the Tail Pointer are on the
	 * same cacheline, the Head Pointer must not be greater than the Tail
	 * Pointer."
	 */
	GEM_BUG_ON(!is_power_of_2(size));
	return (head - tail - CACHELINE_BYTES) & (size - 1);
}