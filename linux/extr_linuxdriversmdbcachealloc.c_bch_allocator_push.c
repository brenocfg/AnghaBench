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
struct cache {int /*<<< orphan*/ * free; } ;

/* Variables and functions */
 unsigned int RESERVE_NR ; 
 size_t RESERVE_PRIO ; 
 scalar_t__ fifo_push (int /*<<< orphan*/ *,long) ; 

__attribute__((used)) static int bch_allocator_push(struct cache *ca, long bucket)
{
	unsigned int i;

	/* Prios/gens are actually the most important reserve */
	if (fifo_push(&ca->free[RESERVE_PRIO], bucket))
		return true;

	for (i = 0; i < RESERVE_NR; i++)
		if (fifo_push(&ca->free[i], bucket))
			return true;

	return false;
}