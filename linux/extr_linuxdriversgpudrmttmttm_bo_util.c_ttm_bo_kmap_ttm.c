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
struct ttm_tt {int /*<<< orphan*/ * pages; } ;
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; } ;
struct ttm_mem_reg {int placement; } ;
struct ttm_buffer_object {struct ttm_tt* ttm; struct ttm_mem_reg mem; } ;
struct ttm_bo_kmap_obj {int /*<<< orphan*/  virtual; int /*<<< orphan*/  bo_kmap_type; int /*<<< orphan*/  page; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int TTM_PL_FLAG_CACHED ; 
 int /*<<< orphan*/  kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_map_kmap ; 
 int /*<<< orphan*/  ttm_bo_map_vmap ; 
 int /*<<< orphan*/  ttm_io_prot (int,int /*<<< orphan*/ ) ; 
 int ttm_tt_populate (struct ttm_tt*,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  vmap (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ttm_bo_kmap_ttm(struct ttm_buffer_object *bo,
			   unsigned long start_page,
			   unsigned long num_pages,
			   struct ttm_bo_kmap_obj *map)
{
	struct ttm_mem_reg *mem = &bo->mem;
	struct ttm_operation_ctx ctx = {
		.interruptible = false,
		.no_wait_gpu = false
	};
	struct ttm_tt *ttm = bo->ttm;
	pgprot_t prot;
	int ret;

	BUG_ON(!ttm);

	ret = ttm_tt_populate(ttm, &ctx);
	if (ret)
		return ret;

	if (num_pages == 1 && (mem->placement & TTM_PL_FLAG_CACHED)) {
		/*
		 * We're mapping a single page, and the desired
		 * page protection is consistent with the bo.
		 */

		map->bo_kmap_type = ttm_bo_map_kmap;
		map->page = ttm->pages[start_page];
		map->virtual = kmap(map->page);
	} else {
		/*
		 * We need to use vmap to get the desired page protection
		 * or to make the buffer object look contiguous.
		 */
		prot = ttm_io_prot(mem->placement, PAGE_KERNEL);
		map->bo_kmap_type = ttm_bo_map_vmap;
		map->virtual = vmap(ttm->pages + start_page, num_pages,
				    0, prot);
	}
	return (!map->virtual) ? -ENOMEM : 0;
}