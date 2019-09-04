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
struct queue {unsigned int nr_levels; unsigned int qs; int /*<<< orphan*/  es; } ;
struct entry {unsigned int level; int /*<<< orphan*/  sentinel; } ;

/* Variables and functions */
 int /*<<< orphan*/  l_del (int /*<<< orphan*/ ,unsigned int,struct entry*) ; 
 struct entry* l_head (int /*<<< orphan*/ ,unsigned int) ; 
 struct entry* l_next (int /*<<< orphan*/ ,struct entry*) ; 

__attribute__((used)) static struct entry *__redist_pop_from(struct queue *q, unsigned level)
{
	struct entry *e;

	for (; level < q->nr_levels; level++)
		for (e = l_head(q->es, q->qs + level); e; e = l_next(q->es, e))
			if (!e->sentinel) {
				l_del(q->es, q->qs + e->level, e);
				return e;
			}

	return NULL;
}