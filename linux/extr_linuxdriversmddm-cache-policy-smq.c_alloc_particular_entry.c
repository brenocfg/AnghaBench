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
struct entry_alloc {unsigned int begin; int /*<<< orphan*/  nr_allocated; int /*<<< orphan*/  free; int /*<<< orphan*/  es; } ;
struct entry {int /*<<< orphan*/  allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct entry* __get_entry (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  init_entry (struct entry*) ; 
 int /*<<< orphan*/  l_del (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct entry*) ; 

__attribute__((used)) static struct entry *alloc_particular_entry(struct entry_alloc *ea, unsigned i)
{
	struct entry *e = __get_entry(ea->es, ea->begin + i);

	BUG_ON(e->allocated);

	l_del(ea->es, &ea->free, e);
	init_entry(e);
	ea->nr_allocated++;

	return e;
}