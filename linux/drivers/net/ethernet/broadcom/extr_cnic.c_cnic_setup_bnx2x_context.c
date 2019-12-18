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
typedef  scalar_t__ u32 ;
struct cnic_local {int ctx_blks; int ctx_align; struct cnic_ctx* ctx_arr; struct cnic_eth_dev* ethdev; } ;
struct cnic_eth_dev {scalar_t__ ctx_tbl_offset; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;
struct cnic_ctx {unsigned long mapping; } ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  cnic_ctx_tbl_wr (struct cnic_dev*,scalar_t__,unsigned long) ; 

__attribute__((used)) static void cnic_setup_bnx2x_context(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_eth_dev *ethdev = cp->ethdev;
	u32 start_offset = ethdev->ctx_tbl_offset;
	int i;

	for (i = 0; i < cp->ctx_blks; i++) {
		struct cnic_ctx *ctx = &cp->ctx_arr[i];
		dma_addr_t map = ctx->mapping;

		if (cp->ctx_align) {
			unsigned long mask = cp->ctx_align - 1;

			map = (map + mask) & ~mask;
		}

		cnic_ctx_tbl_wr(dev, start_offset + i, map);
	}
}