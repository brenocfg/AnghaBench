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
struct cxgb4_tc_u32_table {unsigned int size; struct cxgb4_link* table; } ;
struct cxgb4_link {struct cxgb4_tc_u32_table* tid_map; } ;
struct adapter {struct cxgb4_tc_u32_table* tc_u32; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (struct cxgb4_tc_u32_table*) ; 

void cxgb4_cleanup_tc_u32(struct adapter *adap)
{
	struct cxgb4_tc_u32_table *t;
	unsigned int i;

	if (!adap->tc_u32)
		return;

	/* Free up all allocated memory. */
	t = adap->tc_u32;
	for (i = 0; i < t->size; i++) {
		struct cxgb4_link *link = &t->table[i];

		kvfree(link->tid_map);
	}
	kvfree(adap->tc_u32);
}