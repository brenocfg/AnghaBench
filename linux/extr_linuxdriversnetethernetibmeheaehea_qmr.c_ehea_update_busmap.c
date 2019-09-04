#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct ehea_bmap {int dummy; } ;
struct TYPE_8__ {TYPE_2__** top; } ;
struct TYPE_7__ {TYPE_1__** dir; } ;
struct TYPE_6__ {int* ent; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHEA_DIR_INDEX_SHIFT ; 
 unsigned long EHEA_INDEX_MASK ; 
 unsigned long EHEA_SECTSIZE ; 
 int /*<<< orphan*/  EHEA_TOP_INDEX_SHIFT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PAGE_SIZE ; 
 TYPE_3__* ehea_bmap ; 
 int ehea_calc_index (unsigned long,int /*<<< orphan*/ ) ; 
 int ehea_init_bmap (TYPE_3__*,int,int) ; 
 unsigned long ehea_mr_len ; 
 int /*<<< orphan*/  ehea_rebuild_busmap () ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehea_update_busmap(unsigned long pfn, unsigned long nr_pages, int add)
{
	unsigned long i, start_section, end_section;

	if (!nr_pages)
		return 0;

	if (!ehea_bmap) {
		ehea_bmap = kzalloc(sizeof(struct ehea_bmap), GFP_KERNEL);
		if (!ehea_bmap)
			return -ENOMEM;
	}

	start_section = (pfn * PAGE_SIZE) / EHEA_SECTSIZE;
	end_section = start_section + ((nr_pages * PAGE_SIZE) / EHEA_SECTSIZE);
	/* Mark entries as valid or invalid only; address is assigned later */
	for (i = start_section; i < end_section; i++) {
		u64 flag;
		int top = ehea_calc_index(i, EHEA_TOP_INDEX_SHIFT);
		int dir = ehea_calc_index(i, EHEA_DIR_INDEX_SHIFT);
		int idx = i & EHEA_INDEX_MASK;

		if (add) {
			int ret = ehea_init_bmap(ehea_bmap, top, dir);
			if (ret)
				return ret;
			flag = 1; /* valid */
			ehea_mr_len += EHEA_SECTSIZE;
		} else {
			if (!ehea_bmap->top[top])
				continue;
			if (!ehea_bmap->top[top]->dir[dir])
				continue;
			flag = 0; /* invalid */
			ehea_mr_len -= EHEA_SECTSIZE;
		}

		ehea_bmap->top[top]->dir[dir]->ent[idx] = flag;
	}
	ehea_rebuild_busmap(); /* Assign contiguous addresses for mr */
	return 0;
}