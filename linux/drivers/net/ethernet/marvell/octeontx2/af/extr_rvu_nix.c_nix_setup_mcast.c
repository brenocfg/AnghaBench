#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {int /*<<< orphan*/  rsrc; } ;
struct rvu_hwinfo {int max_vfs_per_pf; TYPE_1__ pkind; } ;
struct rvu {int /*<<< orphan*/  dev; struct rvu_hwinfo* hw; } ;
struct nix_mcast {int replay_pkind; int /*<<< orphan*/  mce_lock; TYPE_2__* mcast_buf; TYPE_2__* mce_ctx; } ;
struct nix_hw {struct nix_mcast mcast; } ;
struct TYPE_4__ {scalar_t__ iova; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int ENOMEM ; 
 unsigned long MC_BUF_CNT ; 
 unsigned long MC_TBL_SIZE ; 
 int /*<<< orphan*/  NIX_AF_CONST3 ; 
 int /*<<< orphan*/  NIX_AF_MC_MIRROR_CONST ; 
 int /*<<< orphan*/  NIX_AF_RX_MCAST_BASE ; 
 int /*<<< orphan*/  NIX_AF_RX_MCAST_BUF_BASE ; 
 int /*<<< orphan*/  NIX_AF_RX_MCAST_BUF_CFG ; 
 int /*<<< orphan*/  NIX_AF_RX_MCAST_CFG ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nix_setup_bcast_tables (struct rvu*,struct nix_hw*) ; 
 int qmem_alloc (int /*<<< orphan*/ ,TYPE_2__**,unsigned long,int) ; 
 int rvu_alloc_rsrc (int /*<<< orphan*/ *) ; 
 int rvu_read64 (struct rvu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nix_setup_mcast(struct rvu *rvu, struct nix_hw *nix_hw, int blkaddr)
{
	struct nix_mcast *mcast = &nix_hw->mcast;
	struct rvu_hwinfo *hw = rvu->hw;
	int err, size;

	size = (rvu_read64(rvu, blkaddr, NIX_AF_CONST3) >> 16) & 0x0F;
	size = (1ULL << size);

	/* Alloc memory for multicast/mirror replication entries */
	err = qmem_alloc(rvu->dev, &mcast->mce_ctx,
			 (256UL << MC_TBL_SIZE), size);
	if (err)
		return -ENOMEM;

	rvu_write64(rvu, blkaddr, NIX_AF_RX_MCAST_BASE,
		    (u64)mcast->mce_ctx->iova);

	/* Set max list length equal to max no of VFs per PF  + PF itself */
	rvu_write64(rvu, blkaddr, NIX_AF_RX_MCAST_CFG,
		    BIT_ULL(36) | (hw->max_vfs_per_pf << 4) | MC_TBL_SIZE);

	/* Alloc memory for multicast replication buffers */
	size = rvu_read64(rvu, blkaddr, NIX_AF_MC_MIRROR_CONST) & 0xFFFF;
	err = qmem_alloc(rvu->dev, &mcast->mcast_buf,
			 (8UL << MC_BUF_CNT), size);
	if (err)
		return -ENOMEM;

	rvu_write64(rvu, blkaddr, NIX_AF_RX_MCAST_BUF_BASE,
		    (u64)mcast->mcast_buf->iova);

	/* Alloc pkind for NIX internal RX multicast/mirror replay */
	mcast->replay_pkind = rvu_alloc_rsrc(&hw->pkind.rsrc);

	rvu_write64(rvu, blkaddr, NIX_AF_RX_MCAST_BUF_CFG,
		    BIT_ULL(63) | (mcast->replay_pkind << 24) |
		    BIT_ULL(20) | MC_BUF_CNT);

	mutex_init(&mcast->mce_lock);

	return nix_setup_bcast_tables(rvu, nix_hw);
}