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
struct pt1_table {int dummy; } ;
struct pt1 {struct pt1_table* tables; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt1_cleanup_table (struct pt1*,struct pt1_table*) ; 
 int pt1_nr_tables ; 
 int /*<<< orphan*/  pt1_unregister_tables (struct pt1*) ; 
 int /*<<< orphan*/  vfree (struct pt1_table*) ; 

__attribute__((used)) static void pt1_cleanup_tables(struct pt1 *pt1)
{
	struct pt1_table *tables;
	int i;

	tables = pt1->tables;
	pt1_unregister_tables(pt1);

	for (i = 0; i < pt1_nr_tables; i++)
		pt1_cleanup_table(pt1, &tables[i]);

	vfree(tables);
}