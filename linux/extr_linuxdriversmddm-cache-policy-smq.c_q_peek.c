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
struct queue {int /*<<< orphan*/  es; scalar_t__ qs; int /*<<< orphan*/  nr_levels; } ;
struct entry {scalar_t__ sentinel; } ;

/* Variables and functions */
 struct entry* l_head (int /*<<< orphan*/ ,scalar_t__) ; 
 struct entry* l_next (int /*<<< orphan*/ ,struct entry*) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct entry *q_peek(struct queue *q, unsigned max_level, bool can_cross_sentinel)
{
	unsigned level;
	struct entry *e;

	max_level = min(max_level, q->nr_levels);

	for (level = 0; level < max_level; level++)
		for (e = l_head(q->es, q->qs + level); e; e = l_next(q->es, e)) {
			if (e->sentinel) {
				if (can_cross_sentinel)
					continue;
				else
					break;
			}

			return e;
		}

	return NULL;
}