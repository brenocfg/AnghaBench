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
struct entry_space {int dummy; } ;
struct entry_alloc {unsigned int nr_allocated; unsigned int begin; struct entry_space* es; int /*<<< orphan*/  free; } ;

/* Variables and functions */
 int /*<<< orphan*/  __get_entry (struct entry_space*,unsigned int) ; 
 int /*<<< orphan*/  l_add_tail (struct entry_space*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_allocator(struct entry_alloc *ea, struct entry_space *es,
			   unsigned begin, unsigned end)
{
	unsigned i;

	ea->es = es;
	ea->nr_allocated = 0u;
	ea->begin = begin;

	l_init(&ea->free);
	for (i = begin; i != end; i++)
		l_add_tail(ea->es, &ea->free, __get_entry(ea->es, i));
}