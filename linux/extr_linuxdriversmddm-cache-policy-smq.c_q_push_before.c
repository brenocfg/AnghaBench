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
struct queue {scalar_t__ qs; int /*<<< orphan*/  es; int /*<<< orphan*/  nr_elts; } ;
struct entry {scalar_t__ level; int /*<<< orphan*/  sentinel; int /*<<< orphan*/  pending_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l_add_before (int /*<<< orphan*/ ,scalar_t__,struct entry*,struct entry*) ; 

__attribute__((used)) static void q_push_before(struct queue *q, struct entry *old, struct entry *e)
{
	BUG_ON(e->pending_work);

	if (!e->sentinel)
		q->nr_elts++;

	l_add_before(q->es, q->qs + e->level, old, e);
}