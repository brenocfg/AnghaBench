#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct topa {int phys; scalar_t__ last; } ;
struct page {int dummy; } ;
typedef  int gfp_t ;
struct TYPE_2__ {int base; int end; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_CAP_topa_multiple_entries ; 
 TYPE_1__* TOPA_ENTRY (struct topa*,int) ; 
 int TOPA_SHIFT ; 
 int __GFP_ZERO ; 
 struct page* alloc_pages_node (int,int,int /*<<< orphan*/ ) ; 
 int cpu_to_node (int) ; 
 struct topa* page_address (struct page*) ; 
 int page_to_phys (struct page*) ; 
 int /*<<< orphan*/  pt_cap_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct topa *topa_alloc(int cpu, gfp_t gfp)
{
	int node = cpu_to_node(cpu);
	struct topa *topa;
	struct page *p;

	p = alloc_pages_node(node, gfp | __GFP_ZERO, 0);
	if (!p)
		return NULL;

	topa = page_address(p);
	topa->last = 0;
	topa->phys = page_to_phys(p);

	/*
	 * In case of singe-entry ToPA, always put the self-referencing END
	 * link as the 2nd entry in the table
	 */
	if (!pt_cap_get(PT_CAP_topa_multiple_entries)) {
		TOPA_ENTRY(topa, 1)->base = topa->phys >> TOPA_SHIFT;
		TOPA_ENTRY(topa, 1)->end = 1;
	}

	return topa;
}