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
struct ttm_tt {int /*<<< orphan*/  num_pages; } ;
struct ttm_mem_reg {int start; } ;
struct qxl_ttm_tt {unsigned long offset; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,struct ttm_mem_reg*,struct ttm_tt*) ; 

__attribute__((used)) static int qxl_ttm_backend_bind(struct ttm_tt *ttm,
				struct ttm_mem_reg *bo_mem)
{
	struct qxl_ttm_tt *gtt = (void *)ttm;

	gtt->offset = (unsigned long)(bo_mem->start << PAGE_SHIFT);
	if (!ttm->num_pages) {
		WARN(1, "nothing to bind %lu pages for mreg %p back %p!\n",
		     ttm->num_pages, bo_mem, ttm);
	}
	/* Not implemented */
	return -1;
}