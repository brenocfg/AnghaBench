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
typedef  int u32 ;
struct regpair {int lo; int hi; } ;
struct cnic_local {int cids_per_blk; int ctx_align; TYPE_1__* ctx_arr; struct cnic_eth_dev* ethdev; } ;
struct cnic_eth_dev {int starting_cid; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {unsigned long mapping; void* ctx; } ;

/* Variables and functions */
 int BNX2X_CONTEXT_MEM_SIZE ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *cnic_get_bnx2x_ctx(struct cnic_dev *dev, u32 cid, int init,
				struct regpair *ctx_addr)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_eth_dev *ethdev = cp->ethdev;
	int blk = (cid - ethdev->starting_cid) / cp->cids_per_blk;
	int off = (cid - ethdev->starting_cid) % cp->cids_per_blk;
	unsigned long align_off = 0;
	dma_addr_t ctx_map;
	void *ctx;

	if (cp->ctx_align) {
		unsigned long mask = cp->ctx_align - 1;

		if (cp->ctx_arr[blk].mapping & mask)
			align_off = cp->ctx_align -
				    (cp->ctx_arr[blk].mapping & mask);
	}
	ctx_map = cp->ctx_arr[blk].mapping + align_off +
		(off * BNX2X_CONTEXT_MEM_SIZE);
	ctx = cp->ctx_arr[blk].ctx + align_off +
	      (off * BNX2X_CONTEXT_MEM_SIZE);
	if (init)
		memset(ctx, 0, BNX2X_CONTEXT_MEM_SIZE);

	ctx_addr->lo = ctx_map & 0xffffffff;
	ctx_addr->hi = (u64) ctx_map >> 32;
	return ctx;
}