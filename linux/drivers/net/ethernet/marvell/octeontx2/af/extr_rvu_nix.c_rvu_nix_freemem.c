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
struct rvu_hwinfo {struct rvu_block* block; } ;
struct rvu_block {int /*<<< orphan*/  aq; } ;
struct rvu {int /*<<< orphan*/  dev; struct rvu_hwinfo* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  bmap; } ;
struct nix_txsch {TYPE_1__ schq; } ;
struct nix_mcast {int /*<<< orphan*/  mce_lock; int /*<<< orphan*/  mcast_buf; int /*<<< orphan*/  mce_ctx; } ;
struct nix_hw {struct nix_mcast mcast; struct nix_txsch* txsch; } ;

/* Variables and functions */
 int BLKADDR_NIX0 ; 
 int /*<<< orphan*/  BLKTYPE_NIX ; 
 int NIX_TXSCH_LVL_CNT ; 
 struct nix_hw* get_nix_hw (struct rvu_hwinfo*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_aq_free (struct rvu*,int /*<<< orphan*/ ) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rvu_nix_freemem(struct rvu *rvu)
{
	struct rvu_hwinfo *hw = rvu->hw;
	struct rvu_block *block;
	struct nix_txsch *txsch;
	struct nix_mcast *mcast;
	struct nix_hw *nix_hw;
	int blkaddr, lvl;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, 0);
	if (blkaddr < 0)
		return;

	block = &hw->block[blkaddr];
	rvu_aq_free(rvu, block->aq);

	if (blkaddr == BLKADDR_NIX0) {
		nix_hw = get_nix_hw(rvu->hw, blkaddr);
		if (!nix_hw)
			return;

		for (lvl = 0; lvl < NIX_TXSCH_LVL_CNT; lvl++) {
			txsch = &nix_hw->txsch[lvl];
			kfree(txsch->schq.bmap);
		}

		mcast = &nix_hw->mcast;
		qmem_free(rvu->dev, mcast->mce_ctx);
		qmem_free(rvu->dev, mcast->mcast_buf);
		mutex_destroy(&mcast->mce_lock);
	}
}