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
struct queue {unsigned int nr_levels; unsigned int* target_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int safe_div (unsigned int,unsigned int) ; 
 unsigned int safe_mod (unsigned int,unsigned int) ; 

__attribute__((used)) static void q_set_targets_subrange_(struct queue *q, unsigned nr_elts, unsigned lbegin, unsigned lend)
{
	unsigned level, nr_levels, entries_per_level, remainder;

	BUG_ON(lbegin > lend);
	BUG_ON(lend > q->nr_levels);
	nr_levels = lend - lbegin;
	entries_per_level = safe_div(nr_elts, nr_levels);
	remainder = safe_mod(nr_elts, nr_levels);

	for (level = lbegin; level < lend; level++)
		q->target_count[level] =
			(level < (lbegin + remainder)) ? entries_per_level + 1u : entries_per_level;
}