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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct rvu_hwinfo {int /*<<< orphan*/ * block; } ;
struct rvu {int /*<<< orphan*/  rsrc_lock; int /*<<< orphan*/  dev; struct rvu_hwinfo* hw; } ;
struct TYPE_3__ {scalar_t__ pcifunc; } ;
struct nix_txsch_free_req {int schq_lvl; int schq; TYPE_1__ hdr; } ;
struct TYPE_4__ {int max; } ;
struct nix_txsch {scalar_t__* pfvf_map; TYPE_2__ schq; } ;
struct nix_hw {struct nix_txsch* txsch; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  BLKTYPE_NIX ; 
 int EINVAL ; 
 int NIX_AF_ERR_AF_LF_INVALID ; 
 int NIX_AF_ERR_TLX_INVALID ; 
 int /*<<< orphan*/  NIX_AF_SMQX_CFG (int) ; 
 int NIX_TXSCH_LVL_SMQ ; 
 int NIX_TXSCH_LVL_TL2 ; 
 scalar_t__ TXSCH_MAP_FUNC (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 struct nix_hw* get_nix_hw (struct rvu_hwinfo*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvu_free_rsrc (TYPE_2__*,int) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,scalar_t__) ; 
 int rvu_get_lf (struct rvu*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int rvu_poll_reg (struct rvu*,int,int /*<<< orphan*/ ,int,int) ; 
 int rvu_read64 (struct rvu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nix_txschq_free_one(struct rvu *rvu,
			       struct nix_txsch_free_req *req)
{
	int lvl, schq, nixlf, blkaddr, rc;
	struct rvu_hwinfo *hw = rvu->hw;
	u16 pcifunc = req->hdr.pcifunc;
	struct nix_txsch *txsch;
	struct nix_hw *nix_hw;
	u32 *pfvf_map;
	u64 cfg;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcifunc);
	if (blkaddr < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	if (!nix_hw)
		return -EINVAL;

	nixlf = rvu_get_lf(rvu, &hw->block[blkaddr], pcifunc, 0);
	if (nixlf < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	lvl = req->schq_lvl;
	schq = req->schq;
	txsch = &nix_hw->txsch[lvl];

	/* Don't allow freeing TL1 */
	if (lvl > NIX_TXSCH_LVL_TL2 ||
	    schq >= txsch->schq.max)
		goto err;

	pfvf_map = txsch->pfvf_map;
	mutex_lock(&rvu->rsrc_lock);

	if (TXSCH_MAP_FUNC(pfvf_map[schq]) != pcifunc) {
		mutex_unlock(&rvu->rsrc_lock);
		goto err;
	}

	/* Flush if it is a SMQ. Onus of disabling
	 * TL2/3 queue links before SMQ flush is on user
	 */
	if (lvl == NIX_TXSCH_LVL_SMQ) {
		cfg = rvu_read64(rvu, blkaddr, NIX_AF_SMQX_CFG(schq));
		/* Do SMQ flush and set enqueue xoff */
		cfg |= BIT_ULL(50) | BIT_ULL(49);
		rvu_write64(rvu, blkaddr, NIX_AF_SMQX_CFG(schq), cfg);

		/* Wait for flush to complete */
		rc = rvu_poll_reg(rvu, blkaddr,
				  NIX_AF_SMQX_CFG(schq), BIT_ULL(49), true);
		if (rc) {
			dev_err(rvu->dev,
				"NIXLF%d: SMQ%d flush failed\n", nixlf, schq);
		}
	}

	/* Free the resource */
	rvu_free_rsrc(&txsch->schq, schq);
	txsch->pfvf_map[schq] = 0;
	mutex_unlock(&rvu->rsrc_lock);
	return 0;
err:
	return NIX_AF_ERR_TLX_INVALID;
}