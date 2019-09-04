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
typedef  int /*<<< orphan*/  u32 ;
struct pt1_table {TYPE_1__* page; } ;
struct pt1 {struct pt1_table* tables; } ;
struct TYPE_2__ {void* next_pfn; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  array_size (int,int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt1_cleanup_table (struct pt1*,struct pt1_table*) ; 
 int pt1_init_table (struct pt1*,struct pt1_table*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt1_init_table_count (struct pt1*) ; 
 int pt1_nr_tables ; 
 int /*<<< orphan*/  pt1_register_tables (struct pt1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (struct pt1_table*) ; 
 struct pt1_table* vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pt1_init_tables(struct pt1 *pt1)
{
	struct pt1_table *tables;
	int i, ret;
	u32 first_pfn, pfn;

	if (!pt1_nr_tables)
		return 0;

	tables = vmalloc(array_size(pt1_nr_tables, sizeof(struct pt1_table)));
	if (tables == NULL)
		return -ENOMEM;

	pt1_init_table_count(pt1);

	i = 0;
	ret = pt1_init_table(pt1, &tables[0], &first_pfn);
	if (ret)
		goto err;
	i++;

	while (i < pt1_nr_tables) {
		ret = pt1_init_table(pt1, &tables[i], &pfn);
		if (ret)
			goto err;
		tables[i - 1].page->next_pfn = cpu_to_le32(pfn);
		i++;
	}

	tables[pt1_nr_tables - 1].page->next_pfn = cpu_to_le32(first_pfn);

	pt1_register_tables(pt1, first_pfn);
	pt1->tables = tables;
	return 0;

err:
	while (i--)
		pt1_cleanup_table(pt1, &tables[i]);

	vfree(tables);
	return ret;
}