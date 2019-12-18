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
typedef  int u8 ;
typedef  int u32 ;
struct bnxt_ring_mem_info {int depth; int nr_pages; int /*<<< orphan*/  pg_tbl_map; int /*<<< orphan*/  pg_tbl; } ;
struct bnxt_ctx_pg_info {int nr_pages; int /*<<< orphan*/ * ctx_dma_arr; int /*<<< orphan*/ * ctx_pg_arr; struct bnxt_ring_mem_info ring_mem; struct bnxt_ctx_pg_info** ctx_pg_tbl; } ;
struct bnxt {int dummy; } ;
typedef  int /*<<< orphan*/  ctx_pg ;

/* Variables and functions */
 int BNXT_PAGE_SIZE ; 
 void* DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_CTX_PAGES ; 
 int MAX_CTX_TOTAL_PAGES ; 
 int bnxt_alloc_ctx_mem_blk (struct bnxt*,struct bnxt_ctx_pg_info*) ; 
 struct bnxt_ctx_pg_info** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct bnxt_ctx_pg_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_alloc_ctx_pg_tbls(struct bnxt *bp,
				  struct bnxt_ctx_pg_info *ctx_pg, u32 mem_size,
				  u8 depth)
{
	struct bnxt_ring_mem_info *rmem = &ctx_pg->ring_mem;
	int rc;

	if (!mem_size)
		return 0;

	ctx_pg->nr_pages = DIV_ROUND_UP(mem_size, BNXT_PAGE_SIZE);
	if (ctx_pg->nr_pages > MAX_CTX_TOTAL_PAGES) {
		ctx_pg->nr_pages = 0;
		return -EINVAL;
	}
	if (ctx_pg->nr_pages > MAX_CTX_PAGES || depth > 1) {
		int nr_tbls, i;

		rmem->depth = 2;
		ctx_pg->ctx_pg_tbl = kcalloc(MAX_CTX_PAGES, sizeof(ctx_pg),
					     GFP_KERNEL);
		if (!ctx_pg->ctx_pg_tbl)
			return -ENOMEM;
		nr_tbls = DIV_ROUND_UP(ctx_pg->nr_pages, MAX_CTX_PAGES);
		rmem->nr_pages = nr_tbls;
		rc = bnxt_alloc_ctx_mem_blk(bp, ctx_pg);
		if (rc)
			return rc;
		for (i = 0; i < nr_tbls; i++) {
			struct bnxt_ctx_pg_info *pg_tbl;

			pg_tbl = kzalloc(sizeof(*pg_tbl), GFP_KERNEL);
			if (!pg_tbl)
				return -ENOMEM;
			ctx_pg->ctx_pg_tbl[i] = pg_tbl;
			rmem = &pg_tbl->ring_mem;
			rmem->pg_tbl = ctx_pg->ctx_pg_arr[i];
			rmem->pg_tbl_map = ctx_pg->ctx_dma_arr[i];
			rmem->depth = 1;
			rmem->nr_pages = MAX_CTX_PAGES;
			if (i == (nr_tbls - 1)) {
				int rem = ctx_pg->nr_pages % MAX_CTX_PAGES;

				if (rem)
					rmem->nr_pages = rem;
			}
			rc = bnxt_alloc_ctx_mem_blk(bp, pg_tbl);
			if (rc)
				break;
		}
	} else {
		rmem->nr_pages = DIV_ROUND_UP(mem_size, BNXT_PAGE_SIZE);
		if (rmem->nr_pages > 1 || depth)
			rmem->depth = 1;
		rc = bnxt_alloc_ctx_mem_blk(bp, ctx_pg);
	}
	return rc;
}