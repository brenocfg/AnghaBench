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
struct entry_alloc {int /*<<< orphan*/  nr_allocated; int /*<<< orphan*/  free; int /*<<< orphan*/  es; } ;
struct entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_entry (struct entry*) ; 
 scalar_t__ l_empty (int /*<<< orphan*/ *) ; 
 struct entry* l_pop_head (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct entry *alloc_entry(struct entry_alloc *ea)
{
	struct entry *e;

	if (l_empty(&ea->free))
		return NULL;

	e = l_pop_head(ea->es, &ea->free);
	init_entry(e);
	ea->nr_allocated++;

	return e;
}