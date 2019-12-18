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
struct queue {unsigned int nr_levels; unsigned int* target_count; int /*<<< orphan*/  es; struct ilist* qs; } ;
struct ilist {unsigned int nr_elts; } ;
struct entry {unsigned int level; } ;

/* Variables and functions */
 struct entry* __redist_pop_from (struct queue*,unsigned int) ; 
 int /*<<< orphan*/  l_add_tail (int /*<<< orphan*/ ,struct ilist*,struct entry*) ; 
 struct entry* l_pop_tail (int /*<<< orphan*/ ,struct ilist*) ; 
 int /*<<< orphan*/  q_set_targets (struct queue*) ; 

__attribute__((used)) static void q_redistribute(struct queue *q)
{
	unsigned target, level;
	struct ilist *l, *l_above;
	struct entry *e;

	q_set_targets(q);

	for (level = 0u; level < q->nr_levels - 1u; level++) {
		l = q->qs + level;
		target = q->target_count[level];

		/*
		 * Pull down some entries from the level above.
		 */
		while (l->nr_elts < target) {
			e = __redist_pop_from(q, level + 1u);
			if (!e) {
				/* bug in nr_elts */
				break;
			}

			e->level = level;
			l_add_tail(q->es, l, e);
		}

		/*
		 * Push some entries up.
		 */
		l_above = q->qs + level + 1u;
		while (l->nr_elts > target) {
			e = l_pop_tail(q->es, l);

			if (!e)
				/* bug in nr_elts */
				break;

			e->level = level + 1u;
			l_add_tail(q->es, l_above, e);
		}
	}
}