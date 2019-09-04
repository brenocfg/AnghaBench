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
struct ilist {int /*<<< orphan*/  nr_elts; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct entry_space {int dummy; } ;
struct entry {int /*<<< orphan*/  sentinel; int /*<<< orphan*/  prev; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 struct entry* l_next (struct entry_space*,struct entry*) ; 
 struct entry* l_prev (struct entry_space*,struct entry*) ; 

__attribute__((used)) static void l_del(struct entry_space *es, struct ilist *l, struct entry *e)
{
	struct entry *prev = l_prev(es, e);
	struct entry *next = l_next(es, e);

	if (prev)
		prev->next = e->next;
	else
		l->head = e->next;

	if (next)
		next->prev = e->prev;
	else
		l->tail = e->prev;

	if (!e->sentinel)
		l->nr_elts--;
}