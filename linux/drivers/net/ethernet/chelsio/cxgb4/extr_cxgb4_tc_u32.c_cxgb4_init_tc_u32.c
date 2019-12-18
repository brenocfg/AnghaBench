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
struct cxgb4_tc_u32_table {unsigned int size; struct cxgb4_link* table; } ;
struct cxgb4_link {struct cxgb4_tc_u32_table* tid_map; } ;
struct TYPE_2__ {unsigned int nftids; } ;
struct adapter {TYPE_1__ tids; } ;

/* Variables and functions */
 unsigned int BITS_TO_LONGS (unsigned int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bitmap_zero (struct cxgb4_tc_u32_table*,unsigned int) ; 
 struct cxgb4_tc_u32_table* kvcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct cxgb4_tc_u32_table*) ; 
 struct cxgb4_tc_u32_table* kvzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_size (struct cxgb4_tc_u32_table*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  table ; 

struct cxgb4_tc_u32_table *cxgb4_init_tc_u32(struct adapter *adap)
{
	unsigned int max_tids = adap->tids.nftids;
	struct cxgb4_tc_u32_table *t;
	unsigned int i;

	if (!max_tids)
		return NULL;

	t = kvzalloc(struct_size(t, table, max_tids), GFP_KERNEL);
	if (!t)
		return NULL;

	t->size = max_tids;

	for (i = 0; i < t->size; i++) {
		struct cxgb4_link *link = &t->table[i];
		unsigned int bmap_size;

		bmap_size = BITS_TO_LONGS(max_tids);
		link->tid_map = kvcalloc(bmap_size, sizeof(unsigned long),
					 GFP_KERNEL);
		if (!link->tid_map)
			goto out_no_mem;
		bitmap_zero(link->tid_map, max_tids);
	}

	return t;

out_no_mem:
	for (i = 0; i < t->size; i++) {
		struct cxgb4_link *link = &t->table[i];

		if (link->tid_map)
			kvfree(link->tid_map);
	}

	if (t)
		kvfree(t);

	return NULL;
}