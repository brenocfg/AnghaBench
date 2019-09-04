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
struct its_node {TYPE_1__* tables; } ;
struct TYPE_2__ {int /*<<< orphan*/ * base; int /*<<< orphan*/  order; } ;

/* Variables and functions */
 int GITS_BASER_NR_REGS ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void its_free_tables(struct its_node *its)
{
	int i;

	for (i = 0; i < GITS_BASER_NR_REGS; i++) {
		if (its->tables[i].base) {
			free_pages((unsigned long)its->tables[i].base,
				   its->tables[i].order);
			its->tables[i].base = NULL;
		}
	}
}