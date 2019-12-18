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
typedef  int u64 ;
struct rvu_pfvf {TYPE_1__* rss_ctx; } ;
struct rvu {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ iova; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int MAX_RSS_INDIR_TBL_SIZE ; 
 int /*<<< orphan*/  NIX_AF_LFX_RSS_BASE (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_RSS_CFG (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_RSS_GRPX (int,int) ; 
 int ilog2 (int) ; 
 int qmem_alloc (int /*<<< orphan*/ ,TYPE_1__**,int,int) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nixlf_rss_ctx_init(struct rvu *rvu, int blkaddr,
			      struct rvu_pfvf *pfvf, int nixlf,
			      int rss_sz, int rss_grps, int hwctx_size)
{
	int err, grp, num_indices;

	/* RSS is not requested for this NIXLF */
	if (!rss_sz)
		return 0;
	num_indices = rss_sz * rss_grps;

	/* Alloc NIX RSS HW context memory and config the base */
	err = qmem_alloc(rvu->dev, &pfvf->rss_ctx, num_indices, hwctx_size);
	if (err)
		return err;

	rvu_write64(rvu, blkaddr, NIX_AF_LFX_RSS_BASE(nixlf),
		    (u64)pfvf->rss_ctx->iova);

	/* Config full RSS table size, enable RSS and caching */
	rvu_write64(rvu, blkaddr, NIX_AF_LFX_RSS_CFG(nixlf),
		    BIT_ULL(36) | BIT_ULL(4) |
		    ilog2(num_indices / MAX_RSS_INDIR_TBL_SIZE));
	/* Config RSS group offset and sizes */
	for (grp = 0; grp < rss_grps; grp++)
		rvu_write64(rvu, blkaddr, NIX_AF_LFX_RSS_GRPX(nixlf, grp),
			    ((ilog2(rss_sz) - 1) << 16) | (rss_sz * grp));
	return 0;
}